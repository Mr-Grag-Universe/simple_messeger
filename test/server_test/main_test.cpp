//
// Created by Stephan on 17.02.2023.
//
#include <gtest/gtest.h>
#include "server.h"
#include "server_test.h"

using namespace MyServer;

TEST(Server, Init) {
    std::shared_ptr<ServerI> server;
    io_service service;
    server = std::dynamic_pointer_cast<ServerI>(std::make_shared<Server>(Server(service)));
    // std::shared_ptr<MyClient::ClientI> client(std::make_shared<MyClient::Client>(MyClient::Client()));
}

TEST_F(ServerTest, connectToDB) {
    server->connectToDB({"0.0.0.0", 32769});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}