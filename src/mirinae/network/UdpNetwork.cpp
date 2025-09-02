#include <mirinae/network/UdpNetwork.h>
#include <iostream>
#include <memory>
#include <string>

namespace mirinae{
	UdpNetwork::UdpNetwork(unsigned short port) 
		: socket_(io_, Endpoint(asio::ip::udp::v4(), port)){}

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

		asio::post(io_, [this]{
			std::error_code ec;
			socket_.close(ec);
		});
		io_.stop();

		if(ioThread_.joinable()) ioThread_.join();
		std::cout << "[net] UDP stopped\n";
	}

	void UdpNetwork::send(const Endpoint& to, const Buffer& buf){
		socket_.async_send_to(asio::buffer(*buf), to, [buf](std::error_code /*ec*/, std::size_t /*n*/){ /*Call back*/ });
	}
}
