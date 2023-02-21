//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSENGER_MESSAGE_H
#define SIMPLE_MESSENGER_MESSAGE_H

#include <iostream>
#include <string>

#include "../include/client.h"

namespace MyClient {

    class Message : public MessageI {
    private:
        size_t _id{};

    };

} // MyClient

#endif //SIMPLE_MESSENGER_MESSAGE_H
