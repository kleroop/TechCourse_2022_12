#ifndef QTWORLD_SHUTDOWN_H
#define QTWORLD_SHUTDOWN_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Process.h>
#include <nlohmann/json.hpp>
#include "../../common/utils/poco_response.h"

class Shutdown : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;
};

#endif
