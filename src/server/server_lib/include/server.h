//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_SERVER_I_H
#define SIMPLE_MESSEGER_SERVER_I_H

#include <iostream>
#include <vector>
#include <map>
#include <thread>

#include <boost/asio.hpp>

using namespace boost::asio;
typedef std::shared_ptr<ip::tcp::socket> socket_ptr;
typedef std::shared_ptr<io_service> io_service_ptr;

namespace MyServer {

    /**
     * some information for creation a connection with a server
     */
    struct ConnectionInfo {
        std::string s_ip;
        size_t port = 2001;
    };

    /**
     * my synchronous server class
     * main functions:
     * 1) accept connections
     * 2) handle created sessions (rest-api)
     * 3) make requests to database
     */
    class ServerI {
    public:
        virtual void waitForConnection() = 0;
        virtual void sessionHandler() = 0;
        virtual void connectToDB(const ConnectionInfo &c_inf = {"", 0}) = 0;
    };

    struct  Session {
        size_t id{};
        std::thread th;
    };

    /**
     * class - interlayer between DB and Server
     */
    class DataBaseI {
    private:
        // change return type
        /// connect to DB
        virtual void connectToDB(const ConnectionInfo &c_inf);
        /// make any request to connected DB
        virtual void makeRequest(const std::string & request);
    };

    class Server : public ServerI {
    private:
        socket_ptr _sock;
        io_service & _service;

        size_t _port{};
        ip::address _address;
        ip::tcp::endpoint _ep;

        std::map<size_t, Session &> _sessions;
    public:
        Server(io_service & service) : _service(service) {}
        ~Server() {
            // "kill" all threads (sessions)
            for (auto & s : _sessions) {
                s.second.th.detach();
            }
        }

        void waitForConnection() override;
        void sessionHandler() override;
        void connectToDB(const ConnectionInfo &c_inf = {"", 0}) override;

    private:

        void setEndpoint(const ip::tcp::endpoint & ep);

        void connect();
        void disconnect();

        size_t request(const std::string & target);
        std::string getResponse();
    };
};

#endif //SIMPLE_MESSEGER_SERVER_I_H
