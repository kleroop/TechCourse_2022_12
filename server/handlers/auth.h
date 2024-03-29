#ifndef QTWORLD_AUTH_UTILS_H
#    define QTWORLD_AUTH_H

#    include <streambuf>
#    include <Poco/JWT/Token.h>
#    include <Poco/JWT/Signer.h>
#    include "handler_includes.h"
#    include "models/auth_model.h"
#    include "poco_request.h"
#    include "phash.h"
#    include "DAL.h"

using namespace nlohmann;

class Auth : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest &request,
                       Poco::Net::HTTPServerResponse &response) override;

private:
    static std::string makeToken(AuthRequest &deserializedRequest);
};

#endif
