#include "main_window.h"
#include "ui_main_window.h"

#include "QMessageBox"
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>

#include <api.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    api = Api();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();
    api.login(adminEmail.toStdString(), adminPassword.toStdString(), [=](const AuthResponse &resp) {
        if (!resp.error.empty()) {
            QMessageBox::information(this, "Connection Error", QString::fromStdString(resp.error));
        } else {
            ui->tokenText->setText(QString::fromStdString(resp.token));
            ui->stackedWidget->setCurrentIndex(1);
        }
    });
}
