//
// Created by Stephan on 17.02.2023.
//

#include "Server.h"
#include "server.h"


using boost::asio::ip::tcp;
using std::string;

int post(boost::asio::io_service & io_service, const string& host, const string& port, const string& page, const string& data, string& reponse_data)
{
    try
    {
        // boost::asio::io_service io_service;
        //If io_service is reused
        if(io_service.stopped())
            io_service.reset();

        //  Obtain all ips under the domain name from dns
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        //  Try to connect to one of the ips until success
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "POST " << page << " HTTP/1.0\r\n";
        request_stream << "Host: " << host << ":" << port << "\r\n";
        request_stream << "Accept: */*\r\n";
        // request_stream << "Content-Length: " << data.length() << "\r\n";
        // request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
        request_stream << "Connection: close\r\n\r\n";
        // request_stream << data;

        // Send the request.
        boost::asio::write(socket, request);
        std::cout << "hi\n";

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            reponse_data = "Invalid response";
            return -2;
        }
        //  If the server returns a non-200, it is considered wrong and does not support redirects such as 301/302
        if (status_code != 200)
        {
            reponse_data = "Response returned with status code != 200 " ;
            return status_code;
        }

        //  The legendary Baotou can be read
        std::string header;
        std::vector<string> headers;
        while (std::getline(response_stream, header) && header != "\r")
            headers.push_back(header);

        //  Read all the remaining data as the package body
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error))
        {
        }

        //Response has data
        if (response.size())
        {
            std::istream response_stream(&response);
            std::istreambuf_iterator<char> eos;
            reponse_data = string(std::istreambuf_iterator<char>(response_stream), eos);
        }

        if (error != boost::asio::error::eof)
        {
            reponse_data = error.message();
            return -3;
        }
    }
    catch(std::exception& e)
    {
        reponse_data = e.what();
        return -4;
    }
    return 0;
}

string host = "127.0.0.1";
string port = "80";
string page = "/auth/login";
string data = "user_name=linbc&password=a";
string response_data;


namespace MyServer {

    void Server::waitForConnection() {
//        socket_ptr sock(new ip::tcp::socket(service));
//        acc.accept(*sock);
//        boost::thread( boost::bind(client_session, sock));
    }

    void Server::sessionHandler() {

    }

    void Server::connectToDB(const ConnectionInfo &c_inf) {
        createSession();
        return;
        std::cout << "begin" << std::endl;
        ip::tcp::endpoint ep;
        if (c_inf.s_ip != "localhost")
            ep = ip::tcp::endpoint( ip::address::from_string(c_inf.s_ip), c_inf.port);
        else
            ep = ip::tcp::endpoint( ip::address::from_string("127.0.0.1"), c_inf.port);
        std::cout << ep.address() << " " << ep.port() << std::endl;
        this->setEndpoint(ep);
        std::cout << _ep << " " << _port << std::endl;
        try {
            this->connect();
        } catch(...) {
            std::cout << "connection error" << std::endl;
        }

        this->createSession();
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

    void Server::disconnect() {
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

    void Server::createSession() {
        std::cout << post(_service, "127.0.0.1", "5432", "/session", "", response_data) << " bytes have been written\n";// this->request("/sessions") << " bytes have been written\n";

        // _session_id = std::stol(this->getResponse());
        std::cout << "id: " << response_data << std::endl;
    }

    size_t Server::request(const std::string & target) {
        std::string payload = "POST " + _address.to_string() + ":" + std::to_string(_port) + target + "\n";
        std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        return _sock->write_some(buffer(payload));
    }
    std::string Server::getResponse() {
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
};

