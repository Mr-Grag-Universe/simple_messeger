#include <QApplication>
#include <QPushButton>
#include "iostream"
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

#include "client_lib/include/client.h"

using namespace std::chrono_literals;
using namespace boost::asio;

int main(int argc, char** argv)
{

    // io_service s;
    // ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 2000);
    // ip::tcp::socket sock(s);
    // sock.connect(ep);

    // std::cout << "tyr\n";

    QApplication app(argc, argv);

    QPushButton button("Hello world !");
    button.show();
    std::cout << "client window created" << std::endl;

    auto service = std::make_shared<io_service>();
    // io_service service;
    auto client = MyClient::CreateInstance<MyClient::ClientI>(service);
    std::cout << "client created" << std::endl;

    client->setUp(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 2000));
    client->Activate(true);
    std::cout << "client created" << std::endl;
    
    while (true) {
        std::this_thread::sleep_for(1s);
        std::cout << "hi" << std::endl;
        client->connectToServer();
    }

    return 0;
}