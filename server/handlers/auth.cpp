#include "auth.h"
#include "auth_utils.h"

void Auth::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    prepareServerResponse(response);
    std::ostream& ostream = response.send();

    json responseJson;

    if (request.getMethod() != "POST")
    {
        responseJson["status"] = 405;
        responseJson["data"] = { {"message", "Method not allowed"} };
        ostream << responseJson.dump();

        return;
    }

    //TODO: add check if request payload wasn't valid json
    json requestData = toJson(request.stream());

    AuthRequest authRequest;
    authRequest.deserialize(requestData);

    if (!authRequest.error.empty())
    {
        responseJson["data"] = { {"message", authRequest.error} };
        responseJson["status"] = 400;

        ostream << responseJson.dump();

        return;
    }

    if (!userExists(authRequest.email, authRequest.password))
    {
        userNotFound(responseJson);
        ostream << responseJson.dump();

        return;
    }

    AuthResponse authResponse(Auth::makeToken(authRequest));
    ostream << authResponse.serialize().dump();
}

 std::string Auth::makeToken(AuthRequest& deserializedRequest)
{
    Poco::JWT::Token token;
    token.setType("JWT");
    token.setSubject(deserializedRequest.password);
    token.payload().set("email", deserializedRequest.email);
    token.setIssuedAt(Poco::Timestamp());

    Poco::JWT::Signer signer(TOKEN_SIGNER);

    return signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
}
