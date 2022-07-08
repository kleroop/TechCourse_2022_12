#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QNetworkReply"
#include <QMainWindow>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void loginResult(QNetworkReply *reply);

private:

    Ui::MainWindow *ui;
    QString loginurl = "https://localhost:5001/login";
};
#endif // MAINWINDOW_H
