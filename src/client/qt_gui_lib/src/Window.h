// Stepan 25.02.2023

#ifndef CLIENT_WINDOW_CLASS_HEADER
#define CLIENT_WINDOW_CLASS_HEADER

#include "../include/qt_gui.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

namespace MyClientGUI {

    struct ChatsList {
        std::shared_ptr<QVBoxLayout> layout;
        std::vector<std::shared_ptr<QPushButton>> chats = {};
        std::shared_ptr<QPushButton> add_contact_button; // = std::make_shared<QPushButton>(new QPushButton());
        // line to write 

        ChatsList(QWidget * w) :
            layout(std::make_shared<QVBoxLayout>()),
            chats({}),
            add_contact_button(std::make_shared<QPushButton>(new QPushButton("add contact", w)))
        {
            layout->addWidget(add_contact_button.get());
        }
    };

    struct Auth {
        std::shared_ptr<QFormLayout> layout;
        std::shared_ptr<QLineEdit> line_edit;
        std::shared_ptr<QPushButton> login_button; // = std::make_shared<QPushButton>(new QPushButton());
        // line to write 

        Auth(QWidget * w) :
                login_button(std::make_shared<QPushButton>(new QPushButton("send", w))),
                layout(std::make_shared<QFormLayout>()),
                line_edit(std::make_shared<QLineEdit>(w))
         {
            // layout->addWidget(line_edit.get());
            layout->addWidget(login_button.get());
            layout->addRow(line_edit.get(), line_edit.get());
         }
    };

    class Window : public WindowI {
    private:
        std::shared_ptr<QWidget> _central_widget;
        /// @brief mode of window
        WindowMode _mode = AUTH;
        /// @brief pointer to client logical class
        MyClient::SharedPtr_Client<MyClient::ClientI> _client;
        /// @brief massive of all at objects, we show in the window in current mode
        // std::vector<std::shared_ptr<QWidget>> _objects = {};
        std::shared_ptr<ChatsList> _chat_list;
        std::shared_ptr<Auth> _auth;

    public:

        Window() {
        }
        ~Window() = default;

        // =========== interface service ============//

        void Delete() override;
        void Activate(bool activate) override;

        friend WindowI * WindowI::CreateInstance();

        // =========== interface functions =========== //

        void setClient(MyClient::SharedPtr_Client<MyClient::ClientI> client) override;
        void updateCondition(WindowMode mode = LIST_OF_CHATS) override;

    private:
        /// @brief update window condition corresponding to it's mode
        /// @tparam mode - asked mode of window
        template <WindowMode mode>
        void _update_condition();

    };

    template <>
    void Window::_update_condition<LIST_OF_CHATS>();
    template <>
    void Window::_update_condition<AUTH>();

};

#endif // CLIENT_WINDOW_CLASS_HEADER