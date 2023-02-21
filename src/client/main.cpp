#include <QApplication>
#include <QPushButton>
#include "iostream"
#include <thread>
#include <chrono>

#include "client_lib/include/client.h"

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QPushButton button("Hello world !");
    button.show();

    return app.exec();
}