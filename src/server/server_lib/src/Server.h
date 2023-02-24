//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_SERVER_H
#define SIMPLE_MESSEGER_SERVER_H

#include <string>

using namespace std;

#include "../include/server.h"

// int post(boost::asio::io_service & io_service, const string& host, const string& port, const string& page, const string& data, string& reponse_data);

namespace MyServer {
    
    using thread_ptr = std::shared_ptr<std::thread>;
    using acceptor_ptr = std::shared_ptr<ip::tcp::acceptor>;

    struct Session {
        size_t id{};
        thread_ptr th;
        socket_ptr sock;
    };


    class Server : public ServerI {
    private:
        io_service & _service;
        acceptor_ptr _acc;

        /// @brief : endpoint server listening to (just 1 now)
        ip::tcp::endpoint _ep;
        /// @brief : endpoint of server DB (just 1 now)
        ip::tcp::endpoint _DB_ep;

        /// @brief flag, talking about connection to server DB
        bool _connected = false;

        /// @brief : map of sessions. include structs with all formal info
        ///          about session with unique session-id - key of the map
        std::map<size_t, Session> _sessions;

        /// @brief : DataBase, connected with server
        ///          Here could be stored all users data
        DB_Ptr _DB;
    public:
        Server(io_service & service) : _service(service) {}
        ~Server() {
            std::cout << "server destructor" << std::endl;
            // "kill" all threads (sessions)
            for (auto & s : _sessions) {
                s.second.th->detach();
            }
            // delete DB?
            _DB->Activate(false);
        }

        // ========= interface functions ======== //

        void waitForConnection() override;
        static void sessionHandler(socket_ptr sock);
        void connectToDB() override;
        void setUp(ip::tcp::endpoint ep, ip::tcp::endpoint DB_ep) override;

        // ========= interface service ======== //

        void Delete() override;
        void Activate(bool activate) override;

        friend ServerI * ServerI::CreateInstance(io_service & service);

        // ================ //

    private:

    };

}


#endif //SIMPLE_MESSEGER_SERVER_H
