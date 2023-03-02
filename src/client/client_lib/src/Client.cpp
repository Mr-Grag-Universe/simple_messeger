//
// Created by Stephan on 17.02.2023.
//

#include "Messenger.h"
#include "client.h"

#include <boost/asio.hpp>

using namespace boost::asio;

namespace MyClient {

    // ============== interface service ============ //
    
    void Client::Delete() {
        delete this;
    }
    void Client::Activate(bool activate) {
        // ip::tcp::socket sock(*_service);
        // _sock = std::make_shared<ip::tcp::socket>(sock);
    }

    ClientI * ClientI::CreateInstance(io_service_ptr service) {
        return static_cast<ClientI *>(new Client(service));
    }

    // ============================== //

    void Client::connectToServer() {
        // if client is already connected to server, throw exeption
        if (_connected) {
            throw std::runtime_error("client is already connected");
        }
        this->connect();

        if (this->authenticate("username", "password")) {
            _connected = true;
        }
        else {
            this->disconnect();
        }

        _connected = true;
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

    void Client::setUp(ip::tcp::endpoint ep) {
        this->setEndpoint(ep);
        try {
            this->connectToServer();
        } catch(const std::exception& e) {
            std::cerr << "connection error: " << e.what() << std::endl;
        }
    }

    bool Client::authenticate(const std::string& username, const std::string& password) {
        std::string auth_message = "AUTH " + username + " " + password + "\n";
        size_t bytes_sent = write(*_sock, buffer(auth_message));
        if (bytes_sent != auth_message.length()) {
            std::cerr << "Error sending auth message" << std::endl;
            return false;
        }

        char response[256];
        size_t bytes_received = read(*_sock, buffer(response, 256));
        std::string response_str(response, bytes_received);
        response_str.erase(std::remove(response_str.begin(), response_str.end(), '\n'), response_str.end());

        if (response_str == "AUTH OK") {
            std::cout << "Authentication successful" << std::endl;
            return true;
        }
        else {
            std::cerr << "Authentication failed: " << response_str << std::endl;
            return false;
        }
    }

    //===============================//

    void Client::setEndpoint(const ip::tcp::endpoint & ep) {
        _ep = ep;
    }

    void Client::connect() {
        std::cout << "try to connect to " << _ep.address() << std::endl;
        boost::system::error_code ec;
        try {
            _sock->connect(_ep, ec);
        } catch (...) {
            std::cerr << "connection error" << std::endl;
            return;
        }

        if(!ec) {
            std::cerr << "successful connection" << std::endl;
        }
        else {
            std::cerr << ec.message() << std::endl;
        }
        
        write(*_sock, buffer("hihihi", 6));
        char data[10];
        size_t len = _sock->read_some(buffer(data));
        if ( len > 0)
            std::cout << data << std::endl;

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
        size_t buff_size = 100;
        std::string response;
        response.resize(buff_size);
        size_t read = _sock->read_some(buffer(response));
        response.resize(read);
        return response;
    }
} // MyClient