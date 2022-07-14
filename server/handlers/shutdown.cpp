#include "shutdown.h"

void Shutdown::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepareServerResponse(response);
    std::ostream& ostream = response.send();

    nlohmann::json responseJson;

    responseJson["status"] = 200;
    responseJson["data"] = "Server will be stopped";

    ostream << responseJson.dump();
    Poco::Process::requestTermination(Poco::Process::id());
}
