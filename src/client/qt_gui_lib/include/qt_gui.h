// Stepan 25.02.2023

#ifndef MY_QT_GUI_FOR_CLIENT_HEADER
#define MY_QT_GUI_FOR_CLIENT_HEADER

#include <QMainWindow>
#include "client.h"

namespace MyClientGUI {

    // ============ help structures =========== //

    enum WindowMode {
        AUTH,
        LIST_OF_CHATS,
        INSIDE_CHAT,
        SETTINGS,
    };

    // ============== interfaces =========== //

    /**
     * @brief : class of main client's window
     *          has several modes of working (template decision)
     *          1. main page - list of all chats
     *          2. inside chat - here you can see messages
     *          3. settings - here there are some tools to edit client
     *             visual parameters
     * 
     */
    class WindowI : public QMainWindow {
    protected:
        ~WindowI() = default;
        WindowI() = default;
    public:

        virtual void Delete() = 0;
        virtual void Activate(bool activate) = 0;

        WindowI & operator=(const WindowI & ) = delete;

        static WindowI * CreateInstance();

        // =========== interface functions =========== //

        /// @brief : connect some client logic class to window to know,
        ///          how to edit this in case user interraction
        /// @param client - pointer to client interface
        virtual void setClient(MyClient::SharedPtr_Client<MyClient::ClientI> client) = 0;
        
        /// @brief : clear all QWidgets from window and construct them newly
        /// @param mode - the mode in which this construction would be processed
        virtual void updateCondition(WindowMode mode = LIST_OF_CHATS) = 0;

    };

    //============== deleters =============//

    struct Window_Deleter {
        void operator()(WindowI* p) const { p->Delete(); }
    };

    //============== pointers and templates =================//

    template <class I> // I — WindowI's heir
    using UniquePtr_Window = std::unique_ptr<I, Window_Deleter>;
    template <class I> // I — has a fabric-function CreateInstance()
    UniquePtr_Window<I> CreateInstanceU() {
        return UniquePtr_Window<I>(I::CreateInstance());
    }
    template <class I> // I — WindowI's heir
    UniquePtr_Window<I> ToPtrU(I* p) {
        return UniquePtr_Window<I>(p);
    }

    template <class I> // I — WindowI's heir
    using SharedPtr_Window = std::shared_ptr<I>;
    template <class I> // I — has a fabric-function CreateInstance()
    SharedPtr_Window<I> CreateInstanceS() {
        return SharedPtr_Window<I>(I::CreateInstance(), Window_Deleter());
    }
    template <class I> // I — WindowI's heir
    SharedPtr_Window<I> ToPtrS(I* p) {
        return SharedPtr_Window<I>(p, Window_Deleter());
    }

    //=======================================================//

};

#endif // MY_QT_GUI_FOR_CLIENT_HEADER