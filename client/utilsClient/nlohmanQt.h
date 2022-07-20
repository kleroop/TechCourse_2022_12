#ifndef QTWORLD_NLOHMANQT_H
#define QTWORLD_NLOHMANQT_H

#include <QNetworkReply>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json toJson(QNetworkReply *reply);

QByteArray toQtByteArray(const json &document);

QString toQString(const json &document);

#endif
