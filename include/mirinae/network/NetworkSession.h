#pragma once
#include <mirinae/network/INetwork.h>

namespace mirinae::network{

    class NetworkSession{
        public :
            NetworkSession(const Endpoint& endpoint);
            ~NetworkSession();

        private :
            int id_;
    };
}