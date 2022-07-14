#include "auth.h"

void Auth::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepareServerResponse(response);
    std::ostream& ostream = response.send();

    nlohmann::json responseJson;

    if (request.getMethod() != "POST")
    {
        responseJson["status"] = 405;
        responseJson["data"] = { {"message", "Method not allowed"} };
        ostream << responseJson.dump();

        return;
    }

    //TODO: add check if request payload wasn't valid json
    nlohmann::json requestData = toJson(request.stream());

    AuthRequest authRequest;
    authRequest.deserialize(requestData);

    if (!authRequest.error().empty())
    {
        responseJson["status"] = 400;
        responseJson["data"] = { {"message", authRequest.error()} };
        ostream << responseJson.dump();

        return;
    }

    // Mocking checking if admin-user with these credentials exists
    //TODO: connect with DAL and do the actual authorization
    if (authRequest.email() != "mail@mail.com" || authRequest.password() != "1234")
    {
        responseJson["status"] = 401;
        responseJson["data"] = { {"message", "User with such credentials doesn't exist"} };
        ostream << responseJson.dump();

        return;
    }

    responseJson["status"] = 200;
    responseJson["data"] = { {"token", "We will generate the token"} };

    ostream << responseJson.dump();
}
