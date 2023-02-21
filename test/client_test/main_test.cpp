//
// Created by Stephan on 17.02.2023.
//
#include <gtest/gtest.h>
#include "client.h"

TEST(Client, Init) {
    std::shared_ptr<MyClient::ClientI> client;
    client = std::dynamic_pointer_cast<MyClient::ClientI>(std::make_shared<MyClient::Client>(MyClient::Client()));
    // std::shared_ptr<MyClient::ClientI> client(std::make_shared<MyClient::Client>(MyClient::Client()));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}