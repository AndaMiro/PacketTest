#pragma once
#include <mirinae/network/UdpNetwork.h>

namespace mirinae::network{
	using PacketCallback = std::function<void(const Endpoint& endpoint, const int id, const void* data, std::size_t n)>;

    class RakNetwork{
        public :
            explicit RakNetwork(std::unique_ptr<UdpNetwork> udp);
			//~RakNetwork() override;

            void start(PacketCallback&& cb);
            void stop();
            void send(Endpoint& to, const Buffer& buf);

            Endpoint connect(const Endpoint& remote);
            void disconnect(Endpoint);
            void onReceive(const Endpoint& endpoint, const void* data, std::size_t n);

        private :
            std::unique_ptr<UdpNetwork> udp_;
            PacketCallback cb_;
    };
}