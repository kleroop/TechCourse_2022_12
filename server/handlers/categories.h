#ifndef QTWORLD_CATEGORIES_UTILS_H
#define QTWORLD_CATEGORIES_H

#include "handler_includes.h"

class GetCategories : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

class UpdateCategories : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

#endif
