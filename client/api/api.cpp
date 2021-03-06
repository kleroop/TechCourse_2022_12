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

void Api::makeRequest(string path, json inp, const std::function<void(const json &)> &f)
{
    QNetworkRequest request(QUrl(QString::fromStdString("http://localhost:5000" + path)));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

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
    makeRequest("/auth", m.serialize(), [=](const json &inp) {
        AuthResponse r;
        r.deserialize(inp);
        f(r);
    });
}
