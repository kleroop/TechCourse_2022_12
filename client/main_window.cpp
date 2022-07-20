#include "main_window.h"
#include "ui_main_window.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::loginResult(QNetworkReply *reply) {
    json replyJson = toJson(reply);

    if ((replyJson["status"]) != 200) {
        QMessageBox::information(this, "Connection Error", toQString(replyJson["data"]["message"]));
    } else {
        ui->tokenText->setText(toQString(replyJson["data"]["token"]));
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_loginBackButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_loginButton_clicked() {
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();

    AuthRequest requestObj(adminEmail.toStdString(), adminPassword.toStdString());
    json requestJson = requestObj.serialize();
    QByteArray data = toQtByteArray(requestJson);

    auto *manager = new QNetworkAccessManager(this);
    QUrl loginPath(loginUrl);
    QNetworkRequest request(loginPath);
    QNetworkReply *reply = manager->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        this->loginResult(reply);
        reply->deleteLater();
    });
}
