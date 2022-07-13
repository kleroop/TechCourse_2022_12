#include "not_found.h"

void NotFound::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepare_server_response(response);
    std::ostream& ostream = response.send();

    nlohmann::json response_json;
    response_json["status"] = 404;
    response_json["data"] = "Not found";

    ostream << response_json.dump();
}
