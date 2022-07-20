#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "QMessageBox"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>

#include "models/api/auth_model.h"
#include "utilsClient/nlohmanQt.h"

#include "nlohmann/json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void on_loginBackButton_clicked();

    void on_loginButton_clicked();

    void loginResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QString loginUrl = "http://localhost:5000/auth";
};

#endif // MAIN_WINDOW_H
