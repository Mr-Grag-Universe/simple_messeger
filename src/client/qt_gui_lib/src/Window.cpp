#include <iostream>

#include <QPushButton>

#include "Window.h"

using namespace MyClientGUI;


// ============== interface service ============ //

void Window::Delete() {
    // this->_client->disconnectFromServer();
    delete this;
}
void Window::Activate(bool activate) {
    this->resize(500, 500);
    this->setWindowTitle("My Messenger");

    this->_central_widget = std::make_shared<QWidget>(this);
    this->setCentralWidget(this->_central_widget.get());

    // this->_chat_list = std::make_shared<ChatsList>(this->_central_widget.get());
    // this->_auth = std::make_shared<Auth>(this->_central_widget.get());

    // _central_widget->setLayout(_)
}

WindowI * WindowI::CreateInstance() {
    return static_cast<WindowI *>(new Window());
}

// ============== template functions ===============//

template<>
void Window::_update_condition<LIST_OF_CHATS>() {
    this->_chat_list = std::make_shared<ChatsList>(this->_central_widget.get());
    std::cout << "update this window" << std::endl;
    // можно написать шаблонную функцию очистки состояния для каждого состояния
    if (_mode == LIST_OF_CHATS) {
        _chat_list->chats.clear();
        _chat_list->add_contact_button->hide();
        // hide text field
    }
    
    auto chats = _client->messenger().getChats();
    for (auto & chat : chats) {
        _chat_list->chats.push_back(std::make_shared<QPushButton>("chat", _central_widget.get()));
        _chat_list->chats.back()->show();
    }
    std::cout << "successful update" << std::endl;
}

template<>
void Window::_update_condition<AUTH>() {
    this->_auth = std::make_shared<Auth>(this->_central_widget.get());
    std::cout << "update this window" << std::endl;
    // можно написать шаблонную функцию очистки состояния для каждого состояния
    if (_mode == LIST_OF_CHATS) {
        // _chat_list->chats.clear();
        // _chat_list->add_contact_button->hide();
        // hide text field
    }
    // _chat_list->add_contact_button->hide();

    // _central_widget->hide();
    
    // нужно добавлять обработчики ситуаций + подключения, но на первое время и так пойдёт
    // _auth = std::make_shared<Auth>(this);
    _central_widget->setLayout(_auth->layout.get());
    _central_widget->show();
    // _auth->line_edit->show();
    // _auth->login_button->show();
    std::cout << "successful update" << std::endl;
}

// ============== interface functions ================ //

void Window::setClient(MyClient::SharedPtr_Client<MyClient::ClientI> client) {
    _client = client;
}

void Window::updateCondition(WindowMode mode) {
    switch (mode) {
    case LIST_OF_CHATS:
        _update_condition<LIST_OF_CHATS>();
        break;
    case AUTH:
        _update_condition<AUTH>();
        break;
    default:
        _update_condition<LIST_OF_CHATS>();
        break;
    }
    _mode = mode;
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
