//
// Created by Stephan on 17.02.2023.
//

#ifndef SIMPLE_MESSEGER_SERVER_H
#define SIMPLE_MESSEGER_SERVER_H

#include <string>
using namespace std;
#include "../include/server.h"
int post(boost::asio::io_service & io_service, const string& host, const string& port, const string& page, const string& data, string& reponse_data);
namespace MyServer {

}


#endif //SIMPLE_MESSEGER_SERVER_H
