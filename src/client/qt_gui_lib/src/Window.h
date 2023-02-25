// Stepan 25.02.2023

#ifndef CLIENT_WINDOW_CLASS_HEADER
#define CLIENT_WINDOW_CLASS_HEADER

#include "../include/qt_gui.h"

namespace MyClientGUI {

    class Window : public WindowI {
    private:

        WindowMode _mode = LIST_OF_CHATS;

        MyClient::SharedPtr_Client<MyClient::ClientI> _client;

        std::vector<std::shared_ptr<QWidget>> _objects = {};

    public:

        Window() = default;
        ~Window() = default;

        // =========== interface service ============//

        void Delete() override;
        void Activate(bool activate) override;

        friend WindowI * WindowI::CreateInstance();

        // =========== interface functions =========== //

        void setClient(MyClient::SharedPtr_Client<MyClient::ClientI> client) override;
        void updateCondition(WindowMode mode = LIST_OF_CHATS) override;

    private:
        template <WindowMode mode>
        void _update_condition();

    };

    template <>
    void Window::_update_condition<LIST_OF_CHATS>();

};

#endif // CLIENT_WINDOW_CLASS_HEADER