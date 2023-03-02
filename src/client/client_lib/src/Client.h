//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CLIENT_H
#define SIMPLE_MESSEGER_CLIENT_H

#include <algorithm>
#include <iostream>
#include <memory>

#include <boost/asio.hpp>

#include "../include/client.h"
#include "Messenger.h"

namespace MyClient {
    using namespace boost::asio;

    class Client : public ClientI {
    private:
        socket_ptr _sock;
        io_service_ptr _service;

        ip::tcp::endpoint _ep;

        bool _connected = false;

        // maybe i could invent something better?
        std::unique_ptr<MessengerI> _messenger;
        std::stringstream _message_stream;
    public:
        Client(io_service_ptr service) :
            _service(service),
            _sock(new ip::tcp::socket(*service)),
            _messenger(dynamic_cast<MessengerI *>(new Messenger(_message_stream)))
        {

            std::cout << "constructor" << std::endl;
            // _messenger = std::move();
        }
        ~Client() { this->disconnect(); }

        // =========== interface service ============//

        void Delete() override;
        void Activate(bool activate) override;

        friend ClientI * ClientI::CreateInstance(io_service_ptr service);

        // =========== interface functions =========== //

        void setUp(ip::tcp::endpoint ep) override;
        void connectToServer() override;
        void disconnectFromServer() override;

        MessengerI & messenger() override;

        void pushStream() override;
        void pullStream() override;

        bool authenticate(const std::string& username, const std::string& password) override;
    private:

        void setEndpoint(const ip::tcp::endpoint & ep);

        void connect();
        void disconnect();

        size_t request(const std::string & target);
        std::string getResponse();

    };

};

#endif //SIMPLE_MESSEGER_CLIENT_H
