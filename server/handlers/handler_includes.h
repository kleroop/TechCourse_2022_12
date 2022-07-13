/**
 * Defines includes for every HTTPRequestHandler subclass to avoid repeating include statements
 * */

#ifndef QTWORLD_HANDLER_INCLUDES_H
#define QTWORLD_HANDLER_INCLUDES_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <nlohmann/json.hpp>
#include "../utils/poco_response.h"

#endif
