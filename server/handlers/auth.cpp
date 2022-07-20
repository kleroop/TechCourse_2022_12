#include "auth.h"

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

    DALUser user;
    DALStatus status = DALUserGetByEmail(&user, authRequest.email.c_str());

    char pwdHash[PHASH_SIZE];
    utils_phash(pwdHash, authRequest.password);

    if (status != DAL_OK || authRequest.email != user.email || strcmp(pwdHash, user.pwdHash) != 0)
    {
        responseJson["data"] = { {"message", "User with such credentials doesn't exist"} };
        responseJson["status"] = 401;

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

    Poco::JWT::Signer signer("0123456789ABCDEF0123456789ABCDEF");

    return signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
}
