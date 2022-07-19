#include "root.h"

void Root::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    prepareServerResponse(response);

    std::ostream& ostr = response.send();

    json  jsonResponse;
    jsonResponse["status"] = 200;
    jsonResponse["data"] = "Hello world";

    ostr << jsonResponse.dump();
}
