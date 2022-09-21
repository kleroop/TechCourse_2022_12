#ifndef QTWORLD_SHUTDOWN_H
#define QTWORLD_SHUTDOWN_H

#include <Poco/Process.h>
#include "handler_includes.h"

using namespace nlohmann;

class Shutdown : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest &request,
                       Poco::Net::HTTPServerResponse &response) override;
};

#endif
