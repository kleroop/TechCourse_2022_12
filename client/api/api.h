#ifndef API_H
#define API_H

#include <models/auth_model.h>
#include <models/categories_model.h>
#include <nlohmann/json.hpp>
#include <QNetworkAccessManager>
#include <functional>

using nlohmann::json;
using std::string;
class Api
{
public:
    Api();
    ~Api();
    void login(string email, string password, const std::function<void(const AuthResponse &)> &f);

    void getCategories(const std::function<void(const CategoriesTreeResponse &)> &f);

    void updateCategories(CategoriesTree &categoriesTree, const std::function<void(const CategoriesTreeResponse &)> &f);

    string token;

private:
    QNetworkAccessManager *manager;
    void makeRequest(string path, json inp, string token, const std::function<void(const json &)> &f);
};

#endif // API_H
