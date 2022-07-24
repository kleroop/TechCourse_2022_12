#ifndef QTWORLD_SERVER_H
#define QTWORLD_SERVER_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>
#include <iostream>
#include "handlers/handlers_factory.h"
#include "DAL/DAL.h"

#define PORT 5000
#define MAX_QUEUED 256
#define MAX_THREADS 64

class Server : public Poco::Util::ServerApplication
{
public:
    Server();
    ~Server();

private:
    Poco::Net::ServerSocket serverSocket;
    Poco::Net::HTTPServerParams* serverParams;
    HandlersFactory* handlersFactory;

    int main(const std::vector<std::string>& args) override;
};

#endif
