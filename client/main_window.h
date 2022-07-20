#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "QNetworkReply"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void on_loginButton_clicked();

    void loginResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QString loginUrl = "https://localhost:5001/login";
};

#endif // MAIN_WINDOW_H
