#ifndef QTWORLD_NLOHMANQT_H
#define QTWORLD_NLOHMANQT_H

#include <QNetworkReply>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json toJson(QNetworkReply *reply);

QByteArray toQtByteArray(json document);

#endif //QTWORLD_NLOHMANQT_H
