#ifndef QTWORLD_AUTH_MODEL_H
#define QTWORLD_AUTH_MODEL_H

#include "models/serializable.h"
#include <Poco/JWT/JWT.h>

using namespace nlohmann;

class AuthRequest : public ISerializable
{
public:
    std::string email;
    std::string password;

    explicit AuthRequest(std::string _email = "", std::string _password = "");
    json serialize() override;
    void deserialize(json data) override;
};

class AuthResponse : public ISerializable
{
public:
    std::string token;

    explicit AuthResponse(std::string _token = "");
    json serialize() override;
    void deserialize(json data) override;
};

#endif
