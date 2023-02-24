//
// Created by Stephan on 19.02.2023.
//

#include "DataBase.h"

namespace MyServer {

    void DataBase::Delete() {
        delete this;
    }
    void DataBase::Activate(bool activate) {
    }

    DataBaseI * DataBaseI::CreateInstance() {
        return static_cast<DataBaseI *>(new DataBase());
    }

    //===========================//

    void DataBase::connectToDB(const ConnectionInfo &c_inf) {
        ip::tcp::endpoint ep( ip::address::from_string(c_inf.s_ip), c_inf.port);
        this->setEndpoint(ep);
        this->connect();

        // createSession();
        // return;
        // std::cout << "begin" << std::endl;
        // ip::tcp::endpoint ep;
        // if (c_inf.s_ip != "localhost")
        //     ep = ip::tcp::endpoint( ip::address::from_string(c_inf.s_ip), c_inf.port);
        // else
        //     ep = ip::tcp::endpoint( ip::address::from_string("127.0.0.1"), c_inf.port);
        // std::cout << ep.address() << " " << ep.port() << std::endl;
        // this->setEndpoint(ep);
        // std::cout << _ep << " " << _port << std::endl;
        // try {
        //     this->connect();
        // } catch(...) {
        //     std::cout << "connection error" << std::endl;
        // }
        // this->createSession();
    }
    void DataBase::makeRequest(const std::string & request) {
        // TODO
    }

    //===============================//

    void DataBase::setEndpoint(const ip::tcp::endpoint & ep) {
        _ep = ep;
        _port = ep.port();
        _address = ep.address();
        std::cout << "ep, port, address are set" << std::endl;
        _sock = socket_ptr(new ip::tcp::socket(*_service));
    }

    void DataBase::connect() {
        std::cout << _address << " " << _port << "\n";
        try {
            _sock->connect(_ep);
            std::cout << "success\n";
            _connected = true;
        } catch (boost::system::system_error & err) {
            std::cerr << "connection error: " << err.what() << std::endl;
            return;
        }
    }

    void DataBase::disconnect() {
        if (_connected) {
            try {
                _sock->shutdown(ip::tcp::socket::shutdown_receive);
                _connected = false;
            } catch (...) {
                std::cout << "unexcited shutdown error" << std::endl;
            }

            _sock->close();
        }
        else
            std::cerr << "connection is already disable" << std::endl;
    }

    void DataBase::createSession() {
        // std::cout << post(_service, "127.0.0.1", "5432", "/session", "", response_data) << " bytes have been written\n";// this->request("/sessions") << " bytes have been written\n";

        // _session_id = std::stol(this->getResponse());
        // std::cout << "id: " << response_data << std::endl;
        // TODO
    }

    size_t DataBase::request(const std::string & target) {
        std::string payload = "POST " + _address.to_string() + ":" + std::to_string(_port) + target + "\n";
        std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        return _sock->write_some(buffer(payload));
    }
    std::string DataBase::getResponse() {
        char buff[1024];
        // std::string buff;
        std::string response;
        try {
            size_t read = _sock->read_some(buffer(buff));
            response = std::string(buff).substr(0, read);
            std::cout << "response: " << response << std::endl;
        } catch(...) {
            std::cout << "read error" << std::endl;
        }
//        this->disconnect();
//        this->connect();
        return response;
    }

} // MyServer