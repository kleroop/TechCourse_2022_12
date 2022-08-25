#ifndef QTWORLD_AUTH_UTILS_H
#define QTWORLD_AUTH_UTILS_H

#include <string>
#include <nlohmann/json.hpp>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include <Poco/JWT/JWTException.h>
#include <poco_response.h>

using namespace nlohmann;

#define TOKEN_SIGNER "0123456789ABCDEF0123456789ABCDEF"

#define AUTH                                                            \
    prepareServerResponse(response);                                    \
    std::ostream& ostream = response.send();                            \
    json responseJson;                                                  \
                                                                        \
    if (!request.hasCredentials())                                      \
    {                                                                   \
        unauthorized(responseJson);                                     \
        ostream << responseJson.dump();                                 \
                                                                        \
        return;                                                         \
    }                                                                   \
                                                                        \
    Poco::JWT::Signer signer(TOKEN_SIGNER);                             \
                                                                        \
    std::string scheme, authInfo;                                       \
    request.getCredentials(scheme, authInfo);                           \
                                                                        \
    try {                                                               \
        Poco::JWT::Token token = signer.verify(authInfo);               \
        if (token.getExpiration() == Poco::Timestamp())                 \
        {                                                               \
            tokenExpired(responseJson);                                 \
            ostream << responseJson.dump();                             \
        }                                                               \
                                                                        \
        auto email = token.payload().getValue<std::string>("email");    \
        auto password = token.getSubject();                             \
                                                                        \
        if (!userExists(email, password))                               \
        {                                                               \
            userNotFound(responseJson);                                 \
            ostream << responseJson.dump();                             \
                                                                        \
            return;                                                     \
        }                                                               \
                                                                        \
    } catch (const Poco::JWT::JWTException& e)                          \
    {                                                                   \
        invalidToken(responseJson);                                     \
        ostream << responseJson.dump();                                 \
        return;                                                         \
    }                                                                   \

bool userExists(std::string& email, std::string& password);

void userNotFound(json& response);

void unauthorized(json& response);

void tokenExpired(json& response);

void invalidToken(json& response);

#endif
