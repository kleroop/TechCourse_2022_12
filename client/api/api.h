#ifndef API_H
#define API_H

#include <models/auth_model.h>
#include <nlohmann/json.hpp>
#include <QNetworkAccessManager>

using nlohmann::json;
using std::string;
class Api
{
public:
    Api();
    void login(string email, string password, const std::function<void(const AuthResponse &)> &f);

private:
    QNetworkAccessManager *manager;
    void makeRequest(string path, json inp, const std::function<void(const json &)> &f);
};

#endif // API_H
