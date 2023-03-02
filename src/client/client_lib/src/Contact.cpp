//
// Created by Stephan on 17.02.2023.
//

#include "Contact.h"

using namespace MyClient;

//========== getters =========//

const std::string & Contact::getName() const {
    return _name;
}
size_t Contact::getId() const {
    return _id;
}

//========== setters =========//

void Contact::setName(const std::string & new_name) {
    _name = new_name;
}

// =============== private functions ============= //

size_t Contact::_chose_id() const {
    return 0;
}