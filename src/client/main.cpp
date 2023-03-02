#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include "iostream"
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

#include "client_lib/include/client.h"
#include "qt_gui_lib/include/qt_gui.h"

using namespace std::chrono_literals;
using namespace boost::asio;

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    // creation of the window
    // QWidget * window = new QMainWindow();
    auto window = MyClientGUI::CreateInstanceU<MyClientGUI::WindowI>();
    window->Activate(true);
    window->show();
    std::cout << "client window created" << std::endl;

    auto service = std::make_shared<io_service>();
    auto client = MyClient::CreateInstanceS<MyClient::ClientI>(service);
    // connect client to gui wrapper
    window->setClient(client);

    client->setUp(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 2000));
    client->Activate(true);
    
    window->updateCondition(MyClientGUI::AUTH);

    return app.exec();
}