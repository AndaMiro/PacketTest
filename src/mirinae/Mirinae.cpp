#include <mirinae/core/Server.h>
#include <mirinae/network/UdpNetwork.h>
#include <atomic>
#include <csignal>
#include <iostream>
#include <memory>

static std::atomic_bool g_quit{false};
static void onSignal(int){ g_quit.store(true); }

int main(int argc, char** argv){
    std::signal(SIGINT, onSignal);
    std::signal(SIGTERM, onSignal);

    unsigned short port = 19132;
    if(argc >= 2){
        try{ port = static_cast<unsigned short>(std::stoi(argv[1])); }
        catch(...){ std::cerr << "Invalid port; using default 19132\n"; }
    }

    auto net = mirinae::MakeUdpNetwork(port);
    mirinae::Server server(std::move(net));

    std::thread stopper([&](){
        while(!g_quit.load()) std::this_thread::sleep_for(std::chrono::milliseconds(50));
        server.requestStop();
    });

    server.run();

    if(stopper.joinable()) stopper.join();
    return 0;
}
