#ifndef QTWORLD_USER_PROFILE_H
#define QTWORLD_USER_PROFILE_H

#include <QWidget>
#include "user_dropdown/user_dropdown.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserProfile;
}
QT_END_NAMESPACE

class UserProfile : public QWidget {
Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);

    ~UserProfile() override;

private:
    Ui::UserProfile *ui;
    UserDropdown *DropdownMenu;
};

#endif
