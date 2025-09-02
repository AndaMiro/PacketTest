#pragma once 
#include <mirinae/network/INetwork.h>
#include <asio.hpp>
#include <atomic>
#include <array>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

namespace mirinae{
	class UdpNetwork final : public INetwork{
		public :
			explicit UdpNetwork(unsigned short port = 19132);
			~UdpNetwork() override;

			void start() override;
			void stop() override;
			void send(const Endpoint& to, const Buffer& buf) override;

		private :
			void doReceive();
			uintptr_t ensureSessionId(const Endpoint& ep);

			asio::io_context io_;
			asio::ip::udp::socket socket_;
			std::thread ioThread_;
			std::atomic_bool running_{false};
	};

	inline std::unique_ptr<INetwork> MakeUdpNetwork(unsigned short port = 19132){
		return std::unique_ptr<INetwork>(new UdpNetwork(port));
	}
}
