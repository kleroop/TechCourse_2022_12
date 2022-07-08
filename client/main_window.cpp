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

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loginResult(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        QString err = reply->errorString();
        QMessageBox::information(this, "Connection Error", err);
    } else {
        QString contents = QString::fromUtf8(reply->readAll());
        ui->tokenText->setText(contents);
        ui->stackedWidget->setCurrentIndex(1);
    }
    reply->deleteLater();
}

void MainWindow::on_loginButton_clicked() {
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();

    QJsonObject loginBody;
    loginBody["email"] = adminEmail;
    loginBody["password"] = adminPassword;
    QJsonDocument doc(loginBody);
    QByteArray data = doc.toJson();

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
