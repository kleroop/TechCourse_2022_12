#include "auth_model.h"

AuthRequest::AuthRequest(std::string email, std::string password) : _email(std::move(email)), _password(std::move(password)) {}

std::string AuthRequest::email()
{
    return _email;
}

std::string AuthRequest::password()
{
    return _password;
}

nlohmann::json AuthRequest::serialize()
{
    nlohmann::json result;

    result["email"] = _email;
    result["password"] = _password;

    return result;
}

void AuthRequest::deserialize(nlohmann::json data)
{
    if (!data.contains("email") || data["email"] == "")
    {
        _error = "Email field is required";
        return;
    }

    _email = data["email"];

    if (!data.contains("password") || data["password"] == "")
    {
        _error = "Password field is required";
        return;
    }

    _password = data["password"];
}
