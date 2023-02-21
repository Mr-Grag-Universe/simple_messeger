//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CLIENTI_H
#define SIMPLE_MESSEGER_CLIENTI_H

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

#include <boost/asio.hpp>

//#include "../src/Client.h"
namespace MyClient {
    using namespace boost::asio;
    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
    typedef boost::shared_ptr<io_service> io_service_ptr;

    /**
     * some information for creation a connection with a server
     */
    struct ConnectionInfo {
        std::string s_ip;
        size_t port = 2001;
    };

    class MessengerI;
    class MessageI;
    /**
     * Client class interface
     * main functions :
     * 1) connect to server
     * 2) creating a session ???
     * 3) authorisation ???
     * 4) letting to use messenger for forming requests to server
     * 5) receiving server responses and another messages
     */
    class ClientI {
        /// connect to server using information from passed info
        virtual bool connectToServer(const ConnectionInfo &c_inf) = 0;
        /// break connection to the server
        virtual void disconnectFromServer() = 0;

        /// return messenger link
        virtual MessengerI & messenger() = 0;

        /// push all requests to server
        virtual void pushStream();
        /// pull all messages from server
        virtual void pullStream();
    };

    class Client : public ClientI {
    private:
        socket_ptr _sock;
        io_service_ptr service;

        size_t _port{};
        ip::address _address;
        ip::tcp::endpoint _ep;

        // maybe i could invent something better?
        std::unique_ptr<MessengerI> _messenger = nullptr;
        std::stringstream _message_stream;
    public:
        explicit Client(socket_ptr sock) : _sock(std::move(sock)) {}
        ~Client() { this->disconnect(); }

        bool connectToServer(const ConnectionInfo & c_inf) override;
        void disconnectFromServer() override;

        MessengerI & messenger() override;

        void pushStream() override;
        void pullStream() override;
    private:

        void setEndpoint(const ip::tcp::endpoint & ep);

        void connect();
        void disconnect();

        size_t request(const std::string & target);
        std::string getResponse();

    };

    /**
     * Messenger - the main object, conducting other substances inside itself
     * has a canal (stream) for connection with client
     * 1) controls chats
     * 2) execute commands from server
     * 3) use and distribute information from server's responses
     */
    class MessengerI {
    public:
        virtual void findContact() = 0;
        virtual void findChat() = 0;
        virtual void addContact() = 0;
        virtual void addChat() = 0;
        virtual void getContact() = 0;
        virtual void getChat() = 0;
    };
    class MessageI {
    public:

    };

    /**
     * chat class interface
     */
    class ChatI {
    public:
        // send?
        virtual void pushMessage(const std::shared_ptr<MessageI> & message) = 0;
    };

}

#include "../src/Chat.h"
#include "../src/Contact.h"
#include "../src/Messenger.h"

#endif //SIMPLE_MESSEGER_CLIENTI_H
