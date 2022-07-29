#ifndef QTWORLD_USER_PROFILE_H
#define QTWORLD_USER_PROFILE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class userProfile;
}
QT_END_NAMESPACE

class userProfile : public QWidget
{
    Q_OBJECT

public:
    explicit userProfile(QWidget *parent = nullptr);
    ~userProfile() override;

    Ui::userProfile *ui;

signals:
    void dropdownButtonClicked();

private slots:
    void onDropdownButtonClicked();

private:

};

#endif
