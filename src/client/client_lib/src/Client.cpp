//
// Created by Stephan on 17.02.2023.
//

#include "Messenger.h"
#include "client.h"

#include <boost/asio.hpp>

namespace MyClient {
    using namespace boost::asio;

    bool Client::connectToServer(const ConnectionInfo &c_inf) {
        ip::tcp::endpoint ep( ip::address::from_string(c_inf.s_ip), c_inf.port);
        this->setEndpoint(ep);
        this->connect();
        return false;
    }
    void Client::disconnectFromServer() {
        this->disconnect();
    }

    MessengerI & Client::messenger() {
        return *_messenger;
    }

    void Client::pushStream() {
        std::string line;
        while (_message_stream >> line) {
            this->request(line);
        }
    }
    void Client::pullStream() {
        std::string s = getResponse();
        while (!s.empty()) {
            s = getResponse();
        }
        // behaviour of the read_something needs to be checked
        // TODO
    }

    //===============================//

    void Client::setEndpoint(const ip::tcp::endpoint & ep) {
        _ep = ep;
        _port = ep.port();
        _address = ep.address();
    }

    void Client::connect() {
        try {
            _sock->connect(_ep);
        } catch (...) {
            std::cerr << "connection error" << std::endl;
            return;
        }
    }

    void Client::disconnect() {
        if (_sock->is_open()) {
            _sock->shutdown(ip::tcp::socket::shutdown_receive);
            _sock->close();
        }
        else
            std::cerr << "connection is already disable" << std::endl;
    }

    size_t Client::request(const std::string & target) {
        std::string payload = "GET " + target + "\n";
        // std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        return _sock->write_some(buffer(payload));
    }
    std::string Client::getResponse() {
        // char * buff = new char[buff_size];
        std::string buff;
        size_t read = _sock->read_some(buffer(buff));
        std::string response = std::string(buff).substr(0, read);
//        this->disconnect();
//        this->connect();
        return response;
    }
} // MyClient