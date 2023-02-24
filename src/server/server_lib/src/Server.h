//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_SERVER_H
#define SIMPLE_MESSEGER_SERVER_H

#include <string>
using namespace std;
#include "../include/server.h"
int post(boost::asio::io_service & io_service, const string& host, const string& port, const string& page, const string& data, string& reponse_data);
namespace MyServer {

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

        // ================ //

        void Delete() override;
        void Activate(bool activate) override;

        friend ServerI * ServerI::CreateInstance(io_service & service);

        // ================ //

    private:

    };

}


#endif //SIMPLE_MESSEGER_SERVER_H
