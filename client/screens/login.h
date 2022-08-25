#ifndef QTWORLD_LOGIN_H
#define QTWORLD_LOGIN_H

#include <QWidget>
#include "api.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Login;
}
QT_END_NAMESPACE

class Login : public QWidget {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    ~Login() override;

private:
    Ui::Login *ui;
    Api api;

signals:
    void onLoginSuccess();

private slots:

    void onLoginBackButtonClicked();

    void onFormTextChanged();

    void onLoginButtonClicked();

    void resizeEvent(QResizeEvent *event) override;
};

#endif // QTWORLD_LOGIN_H
