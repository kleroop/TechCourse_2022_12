#ifndef QTWORLD_USER_LOGIN_H
#define QTWORLD_USER_LOGIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class userLogin;
}
QT_END_NAMESPACE

class userLogin : public QWidget
{
    Q_OBJECT

public:
    explicit userLogin(QWidget *parent = nullptr);
    ~userLogin() override;

signals:
    //void dropdownButtonClicked();

private slots:
    //void onDropdownButtonClicked();

private:
    Ui::userLogin *ui;
};

#endif
