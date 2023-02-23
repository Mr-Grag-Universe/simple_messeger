//
// Created by Stephan on 17.02.2023.
//
#include <gtest/gtest.h>
#include "server.h"
#include "server_test.h"
#include "../../src/server/server_lib/src/Server.h"
using namespace MyServer;

TEST(Server, Init) {
    // std::shared_ptr<ServerI> server;
    io_service service;
//    auto server = Server(service);
//    server.connectToDB({"localhost", 5432});
    // std::shared_ptr<MyClient::ClientI> client(std::make_shared<MyClient::Client>(MyClient::Client()));
    std::string response_data;
    std::cout << post(service, "127.0.0.1", "5432", "/sessions", "", response_data) << " error code\n";// this->request("/sessions") << " bytes have been written\n";

    // _session_id = std::stol(this->getResponse());
    std::cout << "id: " << response_data << std::endl;
}

//TEST_F(ServerTest, connectToDB) {
//    server->connectToDB({"localhost", 5432});
//}

//TEST_F(ServerTest, CreateTheSession) {
//    server->connectToDB({"localhost", 5432});
//    // server->
//}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}