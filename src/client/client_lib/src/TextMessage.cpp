//
// Created by Stephan on 17.02.2023.
//

#include "TextMessage.h"

const std::string & MyClient::TextMessage::getText() const {
    return _text;
}

void MyClient::TextMessage::setText(const std::string &new_text) {
    _text = new_text;
}
