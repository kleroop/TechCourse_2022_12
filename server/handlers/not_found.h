#ifndef QTWORLD_NOT_FOUND_H
#define QTWORLD_NOT_FOUND_H

#include "handler_includes.h"


class NotFound : public Poco::Net::HTTPRequestHandler
{
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;
};

#endif
