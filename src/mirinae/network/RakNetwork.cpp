#include <mirinae/network/RakNetwork.h>

namespace mirinae::network{
    RakNetwork::RakNetwork(std::unique_ptr<UdpNetwork> udp)
		: udp_(std::move(udp)){}

    void RakNetwork::start(){
    }
}