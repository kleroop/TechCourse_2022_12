#include "not_found.h"

void NotFound::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepareServerResponse(response);
    std::ostream& ostream = response.send();

    json responseJson;
    responseJson["status"] = 404;
    responseJson["data"] = "Not found";

    ostream << responseJson.dump();
}
