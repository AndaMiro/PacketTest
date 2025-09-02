#pragma once
#include <mirinae/network/INetwork.h>
#include <atomic>
#include <chrono>
#include <memory>

using namespace mirinae::network;

namespace mirinae{
    class Server{
        public : 
            explicit Server(std::unique_ptr<INetwork> net);
            ~Server();

            void run();
            void onPacket(int id, const void* data, size_t len, uintptr_t session);
            void requestStop(){ quit_.store(true); }

        private :
            void tick(std::chrono::milliseconds dt);

            std::unique_ptr<INetwork> net_;
            std::atomic_bool quit_{false};
    };
}
