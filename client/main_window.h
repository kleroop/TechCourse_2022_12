#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "QNetworkReply"
#include <QMainWindow>
#include <api.h>

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

private:
    Ui::MainWindow *ui;
    Api api;
};

#endif // MAIN_WINDOW_H
