#ifndef QTWORLD_USER_LOGIN_H
#define QTWORLD_USER_LOGIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class UserLogin;
}
QT_END_NAMESPACE

class UserLogin : public QWidget
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = nullptr);

    ~UserLogin() override;

signals:
    // void dropdownButtonClicked();

private slots:
    // void onDropdownButtonClicked();

private:
    Ui::UserLogin *ui;
};

#endif
