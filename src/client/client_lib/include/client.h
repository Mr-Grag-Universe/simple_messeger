//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CLIENTI_H
#define SIMPLE_MESSEGER_CLIENTI_H

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

#include <boost/asio.hpp>

using namespace boost::asio;
using socket_ptr = std::shared_ptr<ip::tcp::socket>;
using io_service_ptr = std::shared_ptr<io_service>;

//#include "../src/Client.h"
namespace MyClient {

    /**
     * some information for creation a connection with a server
     */
    struct ConnectionInfo {
        std::string s_ip;
        size_t port = 2001;
    };

    class MessengerI;
    class MessageI;
    class ChatI;
    class ContactI;

    // ============== interfaces =============== //

    /**
     * Client class interface
     * main functions :
     * 1) connect to server
     * 2) creating a session ???
     * 3) authorisation ???
     * 4) letting to use messenger for forming requests to server
     * 5) receiving server responses and another messages
     */
    class ClientI {
    protected:
        ~ClientI() = default;
    public:

        // ======= interface servise functions ====== //
    
        virtual void Delete() = 0;
        virtual void Activate(bool activate) = 0;
        
        static ClientI * CreateInstance(io_service_ptr service);
        ClientI& operator=(const ClientI&) = delete;

        // ================== //

        virtual void setUp(ip::tcp::endpoint ep) = 0;
        /// connect to server using information from passed info
        virtual void connectToServer() = 0;
        /// break connection to the server
        virtual void disconnectFromServer() = 0;

        /// return messenger link
        virtual MessengerI & messenger() = 0;

        /// push all requests to server
        virtual void pushStream() = 0;
        /// pull all messages from server
        virtual void pullStream() = 0;

        /// function of authentication in the app
        virtual bool authenticate(const std::string& username, const std::string& password) = 0;
    };

    /**
     * Messenger - the main object, conducting other substances inside itself
     * has a canal (stream) for connection with client
     * 1) controls chats
     * 2) execute commands from server
     * 3) use and distribute information from server's responses
     */
    class MessengerI {
    public:
        /// @brief : tries to find contact from yours, which are most correspond to your request
        /// @param some_info - text line, that would be analised to find contact
        /// @return massive of contacts ordered by their corresponding to your request
        virtual std::vector<std::shared_ptr<ContactI>> findContact(const std::string & some_info) = 0;

        /// @brief : tries to find chat from yours, which are most correspond to your request
        /// @param some_info  - text line, that would be analised to find chat
        /// @return massive of chats ordered by their corresponding to your request
        virtual std::vector<std::shared_ptr<ChatI>> findChat(const std::string & some_info) = 0;

        virtual void addContact() = 0;
        virtual void addChat() = 0;
        virtual void getContact() = 0;
        virtual void getChat() = 0;
        virtual std::unordered_map<size_t, std::shared_ptr<ChatI>> & getChats() = 0;
    };
    class MessageI {
    public:

    };

    /**
     * chat class interface
     */
    class ChatI {
    public:
        // send?
        virtual void pushMessage(const std::shared_ptr<MessageI> & message) = 0;
    };

    
    //============== deleters =============//

    struct Client_Deleter {
        void operator()(ClientI* p) const { p->Delete(); }
    };

    //============== pointers and templates =================//

    template <class I> // I — ClientI's heir
    using UniquePtr_Client = std::unique_ptr<I, Client_Deleter>;
    template <class I> // I — has a fabric-function CreateInstance()
    UniquePtr_Client<I> CreateInstanceU(io_service_ptr service) {
        return UniquePtr_Client<I>(I::CreateInstance(service));
    }
    template <class I> // I — ClientI's heir
    UniquePtr_Client<I> ToPtrU(I* p) {
        return UniquePtr_Client<I>(p);
    }

    template <class I> // I — ClientI's heir
    using SharedPtr_Client = std::shared_ptr<I>;
    template <class I> // I — has a fabric-function CreateInstance()
    SharedPtr_Client<I> CreateInstanceS(io_service_ptr service) {
        return SharedPtr_Client<I>(I::CreateInstance(service), Client_Deleter());
    }
    template <class I> // I — ClientI's heir
    SharedPtr_Client<I> ToPtrS(I* p) {
        return SharedPtr_Client<I>(p, Client_Deleter());
    }

    //=======================================================//

    
}

#endif //SIMPLE_MESSEGER_CLIENTI_H
