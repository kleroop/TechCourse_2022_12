#ifndef QTWORLD_HANDLERS_FACTORY_H
#define QTWORLD_HANDLERS_FACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <map>

#include "root.h"
#include "shutdown.h"


enum Handlers {
    RootHandler,
    ShutdownHandler
};

class HandlersFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    HandlersFactory();

    Poco::Net::HTTPRequestHandler *
    createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

private:
    std::map<std::string, Handlers> routes;

    Poco::Net::HTTPRequestHandler* getHandler(Handlers handler);
};


#endif
