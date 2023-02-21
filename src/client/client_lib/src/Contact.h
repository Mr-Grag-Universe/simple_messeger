//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CONTACT_H
#define SIMPLE_MESSEGER_CONTACT_H

#include <iostream>
#include <string>

namespace MyClient {

    class ContactI { ;
    protected:
        virtual ~ContactI() {}

    public:
        //========== getters =========//
        virtual const std::string & getName() const = 0;
        virtual size_t getId() const = 0;

        //========== setters =========//
        virtual void setName(const std::string & new_name) = 0;
    };

    class Contact : ContactI {
    private:
        size_t _id{};
        std::string _name{};
    public:
        ~Contact() override = default;;

        //========== getters =========//
        const std::string & getName() const override;
        size_t getId() const override;

        //========== setters =========//
        void setName(const std::string & new_name) override;
    };

}

#endif //SIMPLE_MESSEGER_CONTACT_H
