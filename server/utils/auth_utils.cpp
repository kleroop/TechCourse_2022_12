#include "auth_utils.h"
#include "phash.h"
#include "DAL.h"

bool userExists(std::string& email, std::string& password)
{
    DAL::User user;
    user.Select("email=$1", { DAL::bind(email) });

    char pwdHash[PHASH_SIZE];
    utils_phash(pwdHash, password);

    return !(user.status != DAL::DAL_OK || email != user.email || strcmp(pwdHash, user.pwdHash.c_str()) != 0);
}

void userNotFound(json& response)
{
    response["data"] = { {"message", "User with such credentials doesn't exist"} };
    response["status"] = 401;
}

void unauthorized(json& response)
{
    response["data"] = { {"message", "Unauthorized"} };
    response["status"] = 401;
}

void tokenExpired(json& response)
{
    response["data"] = { {"message", "Token has been expired"} };
    response["status"] = 401;
}

void invalidToken(json& response)
{
    response["data"] = { {"message", "Invalid token"} };
    response["status"] = 401;
}
