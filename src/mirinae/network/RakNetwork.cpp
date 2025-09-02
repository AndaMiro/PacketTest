#include <mirinae/network/RakNetwork.h>

namespace mirinae::network{
    RakNetwork::RakNetwork(std::unique_ptr<UdpNetwork> udp)
		: udp_(std::move(udp)){}

    void RakNetwork::start(){
      udp_->start([this](const Endpoint& endpoint, const void* data, std::size_t n){
        this->onReceive(endpoint, data, n);
      });
    }

    void RakNetwork::stop(){
      udp_->stop();
    }

    void RakNetwork::send(Endpoint& to, const Buffer& buf){
      udp_->send(to, buf);
    }
}