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

    class DataBase;
    class DataBaseI;
    using DB_Ptr = std::shared_ptr<DataBaseI>;

    /**
     * some information for creation a connection with a server
     */
    struct ConnectionInfo {
        std::string s_ip;
        size_t port = 2001;
    };

    //============== interfaces =============//

    /**
     * my synchronous server class
     * main functions:
     * 1) accept connections
     * 2) handle created sessions (rest-api)
     * 3) make requests to database
     */
    class ServerI {
    protected:
        ~ServerI() = default;
    public:

        // ======= interface servise functions ====== //

        virtual void Delete() = 0;
        virtual void Activate(bool activate) = 0;

        static ServerI * CreateInstance(io_service & service);
        ServerI & operator=(const ServerI &) = delete;

        // ============= //

        virtual void waitForConnection() = 0;
        static void sessionHandler(socket_ptr sock);
        virtual void connectToDB() = 0;
        virtual void setUp(ip::tcp::endpoint ep, ip::tcp::endpoint DB_ep) = 0;
    };

    /**
     * class - interlayer between DB and Server
     */
    class DataBaseI {
    protected:
        ~DataBaseI() = default;
    public:
        virtual void Delete() = 0;
        virtual void Activate(bool activate) = 0;
        
        static DataBaseI * CreateInstance();
        DataBaseI& operator=(const DataBaseI&) = delete;

        //===============================//

        // change return type
        /// connect to DB
        virtual void connectToDB(const ConnectionInfo &c_inf) = 0;
        /// make any request to connected DB
        virtual void makeRequest(const std::string & request) = 0;
    };

    //============== deleters =============//

    struct DB_Deleter {
        void operator()(DataBaseI* p) const { p->Delete(); }
    };
    struct Server_Deleter {
        void operator()(ServerI* p) const { p->Delete(); }
    };

    //============== pointers and templates =================//

    template <class I> // I — ServerI's heir
    using UniquePtr_DB = std::unique_ptr<I, DB_Deleter>;
    template <class I> // I — has a fabric-function CreateInstance()
    UniquePtr_DB<I> CreateInstance() {
        return UniquePtr_DB<I>(I::CreateInstance());
    }
    template <class I> // I — ServerI's heir
    UniquePtr_DB<I> ToPtr(I* p) {
        return UniquePtr_DB<I>(p);
    }

    template <class I> // I — ServerI's heir
    using UniquePtr_Server = std::unique_ptr<I, Server_Deleter>;
    template <class I> // I — has a fabric-function CreateInstance()
    UniquePtr_Server<I> CreateInstance(io_service & service) {
        return UniquePtr_Server<I>(I::CreateInstance(service));
    }
    template <class I> // I — ServerI's heir
    UniquePtr_Server<I> ToPtr(I* p) {
        return UniquePtr_Server<I>(p);
    }

    //=======================================================//

};

#endif //SIMPLE_MESSEGER_SERVER_I_H
