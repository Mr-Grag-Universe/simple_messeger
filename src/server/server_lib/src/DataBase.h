//
// Created by Stephan on 19.02.2023.
//

#ifndef SIMPLE_MESSEGER_DATABASE_H
#define SIMPLE_MESSEGER_DATABASE_H

#include "../include/server.h"

#include <boost/asio.hpp>

namespace MyServer {

    class DataBase : public DataBaseI {
    private:
        socket_ptr _sock;
        io_service_ptr _service;

        size_t _port{};
        ip::address _address;
        ip::tcp::endpoint _ep;

        bool _connected = false;
        size_t _session_id{};

        //====================//
    private:
    protected:
    public:
        DataBase() = default;
        ~DataBase() = default;
        void Delete() override;
        void Activate(bool activate) override;

        friend DataBaseI * DataBaseI::CreateInstance();
        
        //=====================//

        void connectToDB(const ConnectionInfo &c_inf) override;
        void makeRequest(const std::string & request) override;

        template<const size_t type>
        std::shared_ptr<DataBaseI> Create();
    private:
        
        void setEndpoint(const ip::tcp::endpoint & ep);

        void connect();
        void disconnect();
        void createSession();

        size_t request(const std::string & target);
        std::string getResponse();

    };

    // template <> // I — имеет функцию-фабрику CreateInstance()
    // UniquePtr<DataBase> CreateInstance<DataBase>() {
    //     return UniquePtr<DataBase>(DataBase::CreateInstance());
    // }

} // MyServer

#endif //SIMPLE_MESSEGER_DATABASE_H
