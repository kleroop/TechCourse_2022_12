#ifndef QTWORLD_API_H
#define QTWORLD_API_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>

#include "models/api/auth_model.h"
#include "../utilsClient/nlohmanQt.h"

#include "nlohmann/json.hpp"

const std::string BASE_PREFIX = "http://localhost:5000";

void login(QObject *parent, std::string adminEmail, std::string adminPassword, void (*funToCall)(int*));


#endif
