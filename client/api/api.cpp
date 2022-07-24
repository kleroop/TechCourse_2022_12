#include "api.h"

//std::function<void(AuthResponse*)> funToCall

void login(QObject *parent, std::string adminEmail, std::string adminPassword, void (*funToCall)(int*)) {
    AuthRequest requestObj(adminEmail, adminPassword);
    json requestJson = requestObj.serialize();
    QByteArray data = toQtByteArray(requestJson);

    auto *manager = new QNetworkAccessManager(parent);
    QUrl loginPath(QString::fromStdString("http://localhost:5000/auth"));
    QNetworkRequest request(loginPath);
    QNetworkReply *reply = manager->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        json replyJson = toJson(reply);

        AuthResponse responeObj;
        responeObj.deserialize(replyJson);

        reply->deleteLater();

        int five = 5;
        funToCall(&five);
    });
}