#include "shutdown.h"

void Shutdown::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepare_server_response(response);
    std::ostream& ostream = response.send();

    nlohmann::json json_response;

    json_response["status"] = 200;
    json_response["data"] = "Server will be stopped";

    ostream << json_response.dump();
    Poco::Process::requestTermination(Poco::Process::id());
}
