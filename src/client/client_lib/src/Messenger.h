//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_MESSENGER_H
#define SIMPLE_MESSEGER_MESSENGER_H

#include "../include/client.h"
#include "Chat.h"
#include "Contact.h"

namespace MyClient {

    class Messenger : public MessengerI {
        std::stringstream & _message_stream;
        // maybe it would be better to use ordered map, and hash whole contacts
        std::unordered_map<size_t, std::shared_ptr<ChatI>> _chats;
    public:
        explicit Messenger(std::stringstream & message_stream) : _message_stream(message_stream) {
            _chats[0] = std::shared_ptr<ChatI>(new Chat());
        }

        std::vector<std::shared_ptr<ContactI>> findContact(const std::string & some_info) override;
        std::vector<std::shared_ptr<ChatI>> findChat(const std::string & some_info) override;
        void addContact() override;
        void addChat() override;
        void getContact() override;
        void getChat() override;

        // ============ getters ========== //
        std::unordered_map<size_t, std::shared_ptr<ChatI>> & getChats() override;
    };

} // MyClient

#endif //SIMPLE_MESSEGER_MESSENGER_H
