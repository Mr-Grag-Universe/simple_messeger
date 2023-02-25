// Stepan 25.02.2023

#include "Messenger.h"

using namespace MyClient;

void Messenger::findContact() {
    
}
void Messenger::findChat() {
    
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