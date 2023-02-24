//
// Created by Stephan on 19.02.2023.
//
#include "iostream"
#include <thread>
#include <chrono>
#include <memory>

#include "server.h"

using server_ptr = std::shared_ptr<MyServer::ServerI>;
using namespace boost::asio;

int main(int argc, char** argv) {
    io_service service;
    // addresses of server listaning port and it's DB
    ip::tcp::endpoint ep( ip::tcp::v4(), 2000);
    ip::tcp::endpoint DB_ep( ip::address::from_string("127.0.0.1"), 5432);

    ip::tcp::acceptor acc(service, ep);

    // server' setting up
    auto server = server_ptr(MyServer::CreateInstance<MyServer::ServerI>(service));
    server->setUp(ep, DB_ep);
    server->Activate(true);
    server->connectToDB(); // {"127.0.0.1", 5432}

    std::cout << "=====" << std::endl;

    while (true) {
        server->waitForConnection();
    }

    return 0;
}