#pragma once
#include <mirinae/network/UdpNetwork.h>

namespace mirinae::network::raknet{
    enum class Reliability : uint8_t{
        UNRELIABLE, 
        RELIABLE
    };

    struct Datagram{
        uint8_t* data;
        uint16_t len;
        uint16_t mtu;
    };

    struct Payload{
        uint16_t len;
        uint16_t poolId;
        std::atomic<uint16_t> refCnt{1};
        uint8_t* data;
    };

    struct InternalPacket{
        uint8_t pid;
        Reliability flags;
        Payload* payload;
    };

	using PacketCallback = std::function<void(const Endpoint& endpoint, const int id, const void* data, std::size_t n)>;

    class RakNetwork{
        public :
            explicit RakNetwork(std::unique_ptr<UdpNetwork> udp);
			//~RakNetwork() override;

            void start();
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