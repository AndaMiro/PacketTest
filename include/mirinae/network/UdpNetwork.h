#pragma once 
#include <mirinae/network/INetwork.h>

namespace mirinae::network{
	class UdpNetwork final : public INetwork{
		public :
			explicit UdpNetwork(unsigned short port = 19132);
			~UdpNetwork() override;

			void start() override;
			void stop() override;
			void send(const Endpoint& to, const Buffer& buf) override;

			void setReceiveHandler(UdpCallback&& cb);

		private :
			void receivePacket();

			asio::io_context io_;
			asio::ip::udp::socket socket_;
			std::thread ioThread_;
			std::atomic_bool running_{false};
			UdpCallback cb_;
			std::array<std::uint8_t, 1500> rxBuf_{};
			Endpoint rxRemote_{};
	};

	inline std::unique_ptr<INetwork> MakeUdpNetwork(unsigned short port = 19132){
		return std::unique_ptr<INetwork>(new UdpNetwork(port));
	}
}
