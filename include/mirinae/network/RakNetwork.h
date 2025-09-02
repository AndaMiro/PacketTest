#pragma once
#include <mirinae/network/Udpnetwork.h>

namespace mirinae{
    class RakNetwork{
        public :
            explicit RakNetwork(std::unique_ptr<UdpNetwork> udp);
			~RakNetwork() override;

            void start();
            void stop();
            void send(SessionId to, const SendBuffer& buf);

            SessionId connect(const Endpoint& remote);
            void disconnect(SessionId);
            // onReceive(SessionId from, std::span<const uint8_t>) 콜백

        private :
            std::array<std::uint8_t, 1500> rxBuf_{};
			Endpoint rxRemote_{};
    }
}