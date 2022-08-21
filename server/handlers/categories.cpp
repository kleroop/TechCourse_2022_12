#include "categories.h"
#include "auth_utils.h"

void GetCategories::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    AUTH

    responseJson["data"] = { {"message", "Shit bussin"} };
    responseJson["status"] = 200;

    ostream << responseJson.dump(2);
}
