//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CHAT_H
#define SIMPLE_MESSEGER_CHAT_H

#include <iostream>
#include <vector>
#include <memory>

#include "../include/client.h"
#include "Message.h"

namespace MyClient {

    class Chat : public ChatI {
    private:
        /// number of messages in chat
        size_t _size;
        /// messages store (in vector now)
        std::vector<std::shared_ptr<MessageI>> _messages;
    public:
        Chat() = default;
        
        void pushMessage(const std::shared_ptr<MessageI> & message) override;

    };

} // MyClient

#endif //SIMPLE_MESSEGER_CHAT_H
