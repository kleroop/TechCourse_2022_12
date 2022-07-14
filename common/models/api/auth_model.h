#ifndef QTWORLD_AUTH_MODEL_H
#define QTWORLD_AUTH_MODEL_H

#include "../serializable.h"
#include "../../../server/utils/poco_request.h"

class AuthRequest : public ISerializable
{
private:
    std::string _email;
    std::string _password;

public:
    std::string email();
    std::string password();

    explicit AuthRequest(std::string email = "", std::string password = "");
    nlohmann::json serialize() override;
    void deserialize(nlohmann::json data) override;
};

#endif
