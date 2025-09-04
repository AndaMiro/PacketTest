#include <mirinae/network/raknet/RakNetwork.h>

namespace mirinae::network::raknet{
    RakNetwork::RakNetwork(std::unique_ptr<UdpNetwork> udp)
		: udp_(std::move(udp)){}

    void RakNetwork::start(){
      udp_->setReceiveHandler([this](const Endpoint& endpoint, const void* data, std::size_t n){
        this->onReceive(endpoint, data, n);
      }); 
      udp_->start();
    }

    void RakNetwork::stop(){
      udp_->stop();
    }

    void RakNetwork::send(Endpoint& to, const Buffer& buf){
      udp_->send(to, buf);
    }
}