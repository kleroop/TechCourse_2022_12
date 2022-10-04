#include <api.h>
#include <QNetworkReply>

static json toJson(QNetworkReply *reply)
{
    json result;

    if (reply->error() != QNetworkReply::NoError) {
        QString err = reply->errorString();
        result["data"]["message"] = err.toStdString();
        result["status"] = 600;
    } else {
        std::string contents = QString::fromUtf8(reply->readAll()).toStdString();
        result = json::parse(contents);
    }

    return result;
}

static QByteArray toQtByteArray(const json &document)
{
    std::string jsonString = to_string(document);
    const char *jsonCstring = jsonString.c_str();
    QByteArray data(jsonCstring);

    return data;
}

Api::Api()
{
    manager = new QNetworkAccessManager();
}

Api::~Api()
{
    delete manager;
}

void Api::makeRequest(string path, json inp, string token,
                      const std::function<void(const json &)> &f)
{
    QNetworkRequest request(QUrl(QString::fromStdString("http://localhost:5000" + path)));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   /* string s = to_string(inp);
    const char *cs = s.c_str();*/
    string headerData = "Bearer " + token;
    request.setRawHeader("Authorization", QByteArray::fromStdString(headerData));

    QNetworkReply *reply = manager->post(request, toQtByteArray(inp));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        f(toJson(reply));
        reply->deleteLater();
    });
}

// todo: serialize error check with changed makeRequest to use ISerializable
void Api::login(string email, string password, const std::function<void(const AuthResponse &)> &f)
{
    AuthRequest m(email, password);
    makeRequest("/auth", m.serialize(), "", [=](const json &inp) {
        AuthResponse r;
        r.deserialize(inp);
        f(r);
    });
}

void Api::getCategories(const std::function<void(const CategoriesTreeResponse &)> &f)
{
    nlohmann::json j;
    makeRequest("/categories/get", j, this->token, [=](const json &inp) {
        CategoriesTree categoriesTree;
        CategoriesTreeResponse r(categoriesTree);
        r.deserialize(inp);

        for (auto &cat : r.categoriesTree.categories) {
            cat.type = CategoryTypes::CATEGORY;
            for (auto &scat : cat.children) {
                scat.type = CategoryTypes::SUBCATEGORY;
                scat.parent = &cat;
                for (auto &team : scat.children) {
                    team.type = CategoryTypes::TEAM;
                    team.parent = &scat;
                }
            }
        }

        f(r);
    });
}

void Api::updateCategories(CategoriesTree &categoriesTree,
                           const std::function<void(const CategoriesTreeResponse &)> &f)
{
    UpdateCategoriesRequest request(categoriesTree);
    makeRequest("/categories/update", request.serialize(), this->token, [=](const json &inp) {
        CategoriesTree categoriesTree;
        CategoriesTreeResponse r(categoriesTree);
        r.deserialize(inp);
        f(r);
    });
}
