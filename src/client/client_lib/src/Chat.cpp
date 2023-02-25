//
// Created by Stephan on 17.02.2023.
//

#include "Chat.h"

namespace MyClient {

    void Chat::pushMessage(const std::shared_ptr<MessageI> &message) {
        _messages.push_back(message);
    }
    
} // MyClient