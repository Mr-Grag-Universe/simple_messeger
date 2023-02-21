//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_TEXTMESSAGE_H
#define SIMPLE_MESSEGER_TEXTMESSAGE_H

#include <string>

#include "Message.h"

namespace MyClient {

    class TextMessage : public Message {
    private:
        std::string _text;
    public:
        explicit TextMessage(const std::string & text) : _text(text) {}
        explicit TextMessage(const std::string && text) : _text(text) {}

        //========== getters =========//
        const std::string & getText() const;

        //========== setters =========//
        void setText(const std::string & new_text);
    };

}


#endif //SIMPLE_MESSEGER_TEXTMESSAGE_H
