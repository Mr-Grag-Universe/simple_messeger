#include <iostream>

#include <QPushButton>

#include "Window.h"

using namespace MyClientGUI;


// ============== interface service ============ //

void Window::Delete() {
    delete this;
}
void Window::Activate(bool activate) {
    this->resize(500, 500);
    this->setWindowTitle("My Messenger");
}

WindowI * WindowI::CreateInstance() {
    return static_cast<WindowI *>(new Window());
}

// ============== template functions ===============//

template<>
void Window::_update_condition<LIST_OF_CHATS>() {
    std::cout << "update this window" << std::endl;
    _objects.clear();
    auto chats = _client->messenger().getChats();
    for (auto & chat : chats) {
        _objects.push_back(std::make_shared<QPushButton>(this));
        _objects.back()->show();
    }
    std::cout << "successful update" << std::endl;
}

// ============== interface functions ================ //

void Window::setClient(MyClient::SharedPtr_Client<MyClient::ClientI> client) {
    _client = client;
}

void Window::updateCondition(WindowMode mode) {
    _mode = mode;
    switch (_mode) {
    case LIST_OF_CHATS:
        _update_condition<LIST_OF_CHATS>();
        break;
    
    default:
        _update_condition<LIST_OF_CHATS>();
        break;
    }
    
}

// ============== private functions ============= //

// template<>
// void Window::_update_condition<LIST_OF_CHATS>() {
//     std::cout << "update this window" << std::endl;
//     _objects.clear();
//     auto chats = _client->messenger().getChats();
//     for (auto & chat : chats) {
//         _objects.push_back(std::make_shared<QPushButton>(this));
//     }
// }
