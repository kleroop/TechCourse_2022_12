#include "main_window.h"
#include "ui_main_window.h"

#include "QMessageBox"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "nlohmann/json.hpp"
#include <QDebug>

#include "../serialization.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginResult(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QString err = reply->errorString();
        QString code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        QMessageBox::information(this, "Connection Error", code + ": " + err);
    } else {
        QString contents = QString::fromUtf8(reply->readAll());
        ui->tokenText->setText(contents);
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_loginButton_clicked()
{
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();

    json reqJson = loginReq::deserialize(adminEmail.toStdString(), adminPassword.toStdString());

    string jsonString = to_string(reqJson);
    const char *jsonCstring = jsonString.c_str();
    QByteArray data(jsonCstring);

    auto *manager = new QNetworkAccessManager(this);

    QUrl loginPath(loginUrl);

    QNetworkRequest request(loginPath);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        this->loginResult(reply);
        reply->deleteLater();
    });
}
