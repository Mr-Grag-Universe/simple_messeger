// Stepan 25.02.2023

#include "Messenger.h"

using namespace MyClient;

std::vector<std::shared_ptr<ContactI>> Messenger::findContact(const std::string & some_info) {
    return {};
}

std::vector<std::shared_ptr<ChatI>> Messenger::findChat(const std::string & some_info) {
    return {};
}

void Messenger::addContact() {
    
}
void Messenger::addChat() {
    
}
void Messenger::getContact() {
    
}
void Messenger::getChat() {
    
}

std::unordered_map<size_t, std::shared_ptr<ChatI>> & Messenger::getChats() {
    return _chats;
}