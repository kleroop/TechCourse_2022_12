#include "nlohmanQt.h"


//json toJson(QNetworkReply *reply) {
//
//}

QByteArray toQtByteArray(json document) {
    std::string jsonString = to_string(document);
    const char *jsonCstring = jsonString.c_str();
    QByteArray data(jsonCstring);

    return data;
}