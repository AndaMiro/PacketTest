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
            void onReceive(const void* data);

        private :
            std::unique_ptr<UdpNetwork> udp_;
    };
}