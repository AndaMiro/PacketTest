#include <mirinae/core/Server.h>
#include <mirinae/protocol/PacketIds.h>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace mirinae{
    Server::Server(std::unique_ptr<INetwork> net) : net_(std::move(net)){}
    Server::~Server() = default;

    void Server::run(){
        net_->start([this](const void* data){
            //this->onPacket(id, data, len, session);
        });

        auto next = std::chrono::steady_clock::now();
        constexpr auto dt = 50ms;
        std::cout << "[core] Tick loop started (20 TPS)\n";

        while(!quit_.load()){
            tick(dt);
            next += dt;
            std::this_thread::sleep_until(next);
        }

        std::cout << "[core] Stopping network...\n";
        net_->stop();
        std::cout << "[core] Stopped.\n";
    }

    void Server::onPacket(int id, const void* data, size_t len, uintptr_t session){
        (void)data; (void)len;

        switch(id){
            case protocol::PK_PING :
            {
                static constexpr char pong[] = "pong";
                //net_->send(protocol::PK_PONG, pong, sizeof(pong) - 1, session);
                break;
            }

            default :
                // TODO: plugin/handler 
                break;
        }
    }

    void Server::tick(std::chrono::milliseconds /*dt*/){
        // TODO: world/entity/scheduler update.
    }
}
