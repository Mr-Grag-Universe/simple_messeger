//
// Created by Stephan on 17.02.2023.
//

#include "Server.h"
#include "server.h"


namespace MyServer {

    void Server::waitForConnection() {
//        socket_ptr sock(new ip::tcp::socket(service));
//        acc.accept(*sock);
//        boost::thread( boost::bind(client_session, sock));
    }

    void Server::sessionHandler() {

    }

    void Server::connectToDB(const ConnectionInfo &c_inf) {
        std::cout << "begin" << std::endl;
        ip::tcp::endpoint ep( ip::address::from_string(c_inf.s_ip), c_inf.port);
        std::cout << ep.address() << " " << ep.port() << std::endl;
        this->setEndpoint(ep);
        std::cout << _ep << " " << _port << std::endl;
        try {
            this->connect();
        } catch(...) {
            std::cout << "connection error" << std::endl;
        }
    }

    //===============================//

    void Server::setEndpoint(const ip::tcp::endpoint & ep) {
        _ep = ep;
        _port = ep.port();
        _address = ep.address();
        std::cout << "ep, port, address are set" << std::endl;
        _sock = socket_ptr(new ip::tcp::socket(_service));
    }

    void Server::connect() {
        try {
            _sock->connect(ip::tcp::endpoint(ip::address::from_string("localhost:32769"), 5432)); //(_ep);
        } catch (boost::system::system_error & err) {
            std::cerr << "connection error: " << err.what() << std::endl;
            return;
        }
    }

    void Server::disconnect() {
        if (_sock->is_open()) {
            _sock->shutdown(ip::tcp::socket::shutdown_receive);
            _sock->close();
        }
        else
            std::cerr << "connection is already disable" << std::endl;
    }

    size_t Server::request(const std::string & target) {
        std::string payload = "GET " + target + "\n";
        // std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        return _sock->write_some(buffer(payload));
    }
    std::string Server::getResponse() {
        // char * buff = new char[buff_size];
        std::string buff;
        size_t read = _sock->read_some(buffer(buff));
        std::string response = std::string(buff).substr(0, read);
//        this->disconnect();
//        this->connect();
        return response;
    }
};

