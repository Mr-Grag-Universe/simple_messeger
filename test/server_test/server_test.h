//
// Created by Stephan on 21.02.2023.
//

#ifndef SIMPLE_MESSEGER_SERVER_TEST_H
#define SIMPLE_MESSEGER_SERVER_TEST_H

#include <gtest/gtest.h>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace MyServer;

class ServerTest : public ::testing::Test {
protected:
    // std::shared_ptr<MyServer::ServerI> server = std::make_shared<Server>(Server(this->service));
    io_service service;
public:
    void SetUp() override {
        std::cout << "setup" << std::endl;
        ip::tcp::endpoint ep( ip::tcp::v4(), 2000);
        ip::tcp::acceptor acc(service, ep);
        // server =
        // auto server_i = std::dynamic_pointer_cast<MyServer::ServerI>(server);
        // server->connectToDB({"0.0.0.0:32768", 5432});
    }
};

#endif //SIMPLE_MESSEGER_SERVER_TEST_H
