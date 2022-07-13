#include "root.h"

void Root::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    prepare_server_response(response);

    std::ostream& ostr = response.send();

    nlohmann::json  json_response;
    json_response["status"] = 200;
    json_response["data"] = "Hello world";

    ostr << json_response.dump();
}
