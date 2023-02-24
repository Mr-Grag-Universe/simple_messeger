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

    class DataBase;
    /**
     * class - interlayer between DB and Server
     */
    class DataBaseI;
    using DB_Ptr = std::shared_ptr<DataBaseI>;
    class DataBaseI {
    protected:
        ~DataBaseI() = default;
    public:
        virtual void Delete() = 0;
        virtual void Activate(bool activate) = 0;
        
        // static DataBaseI* CreateInstance(); // fabric-function
        static DataBaseI * CreateInstance();
        DataBaseI& operator=(const DataBaseI&) = delete;

        // fabric function for this interface
        // template<const size_t type>
        // static std::shared_ptr<DataBaseI> Create() = 0;

        //===============================//

        // change return type
        /// connect to DB
        virtual void connectToDB(const ConnectionInfo &c_inf) = 0;
        /// make any request to connected DB
        virtual void makeRequest(const std::string & request) = 0;
    };

    struct DB_Deleter {
        void operator()(DataBaseI* p) const { p->Delete(); }
    };

    //============== pointers and templates =================//

    template <class I> // I — наследник IBase
    using UniquePtr = std::unique_ptr<I, DB_Deleter>;
    template <class I> // I — имеет функцию-фабрику CreateInstance()
    UniquePtr<I> CreateInstance() {
        return UniquePtr<I>(I::CreateInstance());
    }
    template <class I> // I — наследник IBase
    UniquePtr<I> ToPtr(I* p) {
        return UniquePtr<I>(p);
    }

    //=======================================================//

    class Server : public ServerI {
    private:
        socket_ptr _sock;
        io_service & _service;

        size_t _port{};
        ip::address _address;
        ip::tcp::endpoint _ep;

        bool _connected = false;
        size_t _session_id{};

        std::map<size_t, Session &> _sessions;
        DB_Ptr _DB;
    public:
        Server(io_service & service) : _service(service) {}
        ~Server() {
            std::cout << "server destructor" << std::endl;
            // "kill" all threads (sessions)
            for (auto & s : _sessions) {
                s.second.th.detach();
            }
            // delete DB?
            // this->disconnect();
        }

        void waitForConnection() override;
        void sessionHandler() override;
        void connectToDB(const ConnectionInfo &c_inf = {"127.0.0.1", 0}) override;

    private:

    };
};

#endif //SIMPLE_MESSEGER_SERVER_I_H
