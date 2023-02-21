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
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

int main(int argc, char** argv) {
    io_service service;
    ip::tcp::endpoint ep( ip::tcp::v4(), 2000);
    ip::tcp::acceptor acc(service, ep);

    server_ptr server = std::make_shared<MyServer::Server>(service);
    server->connectToDB({"0.0.0.0:32768", 5432});
    while (true) {
        server->waitForConnection();
    }

    return 0;
}