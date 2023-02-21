//
// Created by Stephan on 19.02.2023.
//

#include "DataBase.h"

namespace MyServer {

    void DataBase::connectToDB(const ConnectionInfo &c_inf) {
        ip::tcp::endpoint ep( ip::address::from_string(c_inf.s_ip), c_inf.port);
        this->setEndpoint(ep);
        this->connect();
    }
    void DataBase::makeRequest(const std::string & request) {
        // TODO
    }

    //===============================//

    void DataBase::setEndpoint(const ip::tcp::endpoint & ep) {
        _ep = ep;
        _port = ep.port();
        _address = ep.address();
    }

    void DataBase::connect() {
        try {
            _sock->connect(_ep);
        } catch (...) {
            std::cerr << "connection error" << std::endl;
            return;
        }
    }

    void DataBase::disconnect() {
        if (_sock->is_open()) {
            _sock->shutdown(ip::tcp::socket::shutdown_receive);
            _sock->close();
        }
        else
            std::cerr << "connection is already disable" << std::endl;
    }

    size_t DataBase::request(const std::string & target) {
        std::string payload = "GET " + target + "\n";
        // std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        return _sock->write_some(buffer(payload));
    }
    std::string DataBase::getResponse() {
        // char * buff = new char[buff_size];
        std::string buff;
        size_t read = _sock->read_some(buffer(buff));
        std::string response = std::string(buff).substr(0, read);
//        this->disconnect();
//        this->connect();
        return response;
    }

} // MyServer