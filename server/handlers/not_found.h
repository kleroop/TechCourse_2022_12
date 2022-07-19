#ifndef QTWORLD_NOT_FOUND_H
#define QTWORLD_NOT_FOUND_H

#include "handler_includes.h"

using namespace nlohmann;

class NotFound : public Poco::Net::HTTPRequestHandler
{
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;
};

#endif
