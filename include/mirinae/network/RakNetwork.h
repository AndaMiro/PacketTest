#pragma once
#include <mirinae/network/UdpNetwork.h>

namespace mirinae::network{
    class RakNetwork{
        public :
            explicit RakNetwork(std::unique_ptr<UdpNetwork> udp);
			//~RakNetwork() override;

            void start();
            void stop();
            void send(Endpoint to, const Buffer& buf);

            Endpoint connect(const Endpoint& remote);
            void disconnect(Endpoint);
            // onReceive(SessionId from, std::span<const uint8_t>) 콜백

        private :
            std::unique_ptr<UdpNetwork> udp_;
            std::array<std::uint8_t, 1500> rxBuf_{};
			Endpoint rxRemote_{};
    };
}