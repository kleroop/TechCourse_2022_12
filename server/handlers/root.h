#ifndef QTWORLD_ROOT_H
#define QTWORLD_ROOT_H

#include "handler_includes.h"

using namespace nlohmann;

class Root : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

#endif
