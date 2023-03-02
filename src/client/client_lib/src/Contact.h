//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_CONTACT_H
#define SIMPLE_MESSEGER_CONTACT_H

#include <iostream>
#include <string>

namespace MyClient {

    /**
     * @brief : class of contact - brief contact info about
     *          user of my messenger. Contain the following info fields:
     *          1. id - unique id in the system
     *          2. name - real full name of the person
     *          2. username/login/nickname - name, that other users can see and contact
     */
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
        const size_t _id{};
        std::string _name;
    public:
        Contact(const std::string & name) : _name(name), _id(_chose_id()) {}
        ~Contact() override = default;;

        //========== getters =========//

        const std::string & getName() const override;
        size_t getId() const override;

        //========== setters =========//

        void setName(const std::string & new_name) override;

    private:
        /// @brief : chose id by some system logic - send request to DB on server to do this
        size_t _chose_id() const;
    };

}

#endif //SIMPLE_MESSEGER_CONTACT_H
