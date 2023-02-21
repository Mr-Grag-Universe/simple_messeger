//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CLIENT_H
#define SIMPLE_MESSEGER_CLIENT_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "../include/client.h"

#include <boost/asio.hpp>

namespace MyClient {
    using namespace boost::asio;
//    /**
//     * some information for creation a connection with a server
//     */
//    struct ConnectionInfo {
//        std::string s_ip;
//    };
//
//    /**
//     * Client class interface
//     * main functions :
//     * 1) connect to server
//     * 2) creating a session ???
//     * 3) authorisation ???
//     * 4) letting to use messenger for forming requests to server
//     * 5) receiving server responses and another messages
//     */
//    class ClientI {
//        virtual bool connectToServer(const ConnectionInfo & c_inf) = 0;
//    };

//    class Client : public ClientI {
//    private:
//        std::unique_ptr<MessengerI> _messenger = nullptr;
//    public:
//        bool connectToServer(const ConnectionInfo & c_inf) override {return true;}
//    };
};

#endif //SIMPLE_MESSEGER_CLIENT_H
