#ifndef QTWORLD_HOME_H
#define QTWORLD_HOME_H

#include <QWidget>
#include "QPushButton"

#include "user_profile/user_profile.h"
#include "user_profile/user_dropdown/user_dropdown.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home() override;

    userProfile* userProfileWidget;
    userDropdown* dropdownMenu;

private slots:
    void onDropdownButtonClicked();

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Home *ui;
    void moveDropdown();
};

#endif // QTWORLD_HOME_H
