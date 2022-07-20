#include "nlohmanQt.h"

json toJson(QNetworkReply *reply) {
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

QByteArray toQtByteArray(const json &document) {
    std::string jsonString = to_string(document);
    const char *jsonCstring = jsonString.c_str();
    QByteArray data(jsonCstring);

    return data;
}

QString toQString(const json &document) {
    QString s = QString::fromStdString(to_string(document).c_str());
    return s;
}