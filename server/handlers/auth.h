#ifndef QTWORLD_AUTH_H
#define QTWORLD_AUTH_H

#include <streambuf>
#include "handler_includes.h"
#include "../../common/models/api/auth_model.h"
#include "../utils/poco_request.h"

class Auth : public Poco::Net::HTTPRequestHandler
{
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

#endif
