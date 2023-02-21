//
// Created by Stephan on 19.02.2023.
//

#ifndef SIMPLE_MESSEGER_DATABASE_H
#define SIMPLE_MESSEGER_DATABASE_H

#include "../include/server.h"

#include <boost/asio.hpp>

namespace MyServer {

    class DataBase : DataBaseI {
    private:
        socket_ptr _sock;
        io_service_ptr service;

        size_t _port{};
        ip::address _address;
        ip::tcp::endpoint _ep;

    public:
        void connectToDB(const ConnectionInfo &c_inf) override;
        void makeRequest(const std::string & request) override;

    private:

        void setEndpoint(const ip::tcp::endpoint & ep);

        void connect();
        void disconnect();

        size_t request(const std::string & target);
        std::string getResponse();
    };

} // MyServer

#endif //SIMPLE_MESSEGER_DATABASE_H
