#include "auth_model.h"

AuthRequest::AuthRequest(std::string _email, std::string _password) : email(std::move(_email)), password(std::move(_password)) {}

json AuthRequest::serialize()
{
    json result;

    result["email"] = email;
    result["password"] = password;

    return result;
}

void AuthRequest::deserialize(json data)
{
    if (!data.contains("email") || data["email"] == "")
    {
        error = "Email field is required";
        return;
    }

    email = data["email"];

    if (!data.contains("password") || data["password"] == "")
    {
        error = "Password field is required";
        return;
    }

    password = data["password"];
}

AuthResponse::AuthResponse(std::string _token) : token(std::move(_token)) {}

json AuthResponse::serialize()
{
    json response;

    response["data"] = { {"token", token} };
    response["status"] = 200;

    return response;
}

void AuthResponse::deserialize(json data)
{
    if (data["status"] != 200)
    {
        error = data["data"]["message"];
        return;
    }

    token = data["data"]["token"];
}
