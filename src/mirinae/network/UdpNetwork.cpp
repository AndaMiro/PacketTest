#include <mirinae/network/UdpNetwork.h>
#include <iostream>
#include <memory>
#include <string>

namespace mirinae{
	UdpNetwork::UdpNetwork(unsigned short port) 
		: socket_(io_, Endpoint(udp::v4(), port)){}

	UdpNetwork::~UdpNetwork(){
		stop();
	}

	void UdpNetwork::start(){
		if(running_.exchange(true)) return;
		
		doReceive();
		ioThread_ = std::thread([this]{
			try{ io_.run(); }
			catch(const std::exception& e){
				std::cerr << "[net] io.run exception: " << e.what() << "\n";
			}
		});
		std::cout << "[net] UDP started on " << socket_.local_endpoint() << "\n";
	}

	void UdpNetwork::stop(){
		if(!running_.exchange(false)) return;

		io_.post([this]{
			std::error_code ec;
			socket_.close(ec);
		});
		io_.stop();

		if(ioThread_.joinable()) ioThread_.join();
		std::cout << "[net] UDP stopped\n";
	}

	void UdpNetwork::send(int id, const void* data, size_t len, uintptr_t session){
		auto buf = std::make_shared<std::vector<std::uint8_t>>();
		buf->reserve(1 + len);
		buf->push_back(static_cast<std::uint8_t>(id & 0xFF));

		if(data && len){
			const auto* p = static_cast<const std::uint8_t*>(data);
			buf->insert(buf->end(), p, p + len);
		}

		udp::endpoint ep;
		{
			std::lock_guard<std::mutex> lk(mu_);
			auto it = id2ep_.find(session);
			
			if(it == id2ep_.end()) return;

			ep = it->second;
		}

		socket_.async_send_to(asio::buffer(*buf), ep, [buf](std::error_code, std::size_t){});
	}

	void UdpNetwork::doReceive(){
		socket_.async_receive_from(asio::buffer(rxBuf_), rxRemote_, [this](std::error_code ec, std::size_t n){
			if(!running_.load()) return;

			if(ec){
				if(ec != asio::error::operation_aborted) std::cerr << "[net] recv error: " << ec.message() << "\n";

				if(running_.load()) doReceive();
				return;
			}

			if(n >= 1 && cb_){
				int id = rxBuf_[0];
				uintptr_t sess = ensureSessionId(rxRemote_);
				const void* payload = (n > 1) ? (rxBuf_.data() + 1) : nullptr;
				size_t plen = (n > 1) ? (n - 1) : 0;
				cb_(id, payload, plen, sess);
			}

			doReceive();
		});
	}

	uintptr_t UdpNetwork::ensureSessionId(const udp::endpoint& ep){
		const auto key = toKey(ep);
		std::lock_guard<std::mutex> lk(mu_);
		auto it = ep2id_.find(key);

		if(it != ep2id_.end()) return it->second;

		auto id = nextId_++;
		ep2id_[key] = id;
		id2ep_[id] = ep;
		return id;
	}
}
