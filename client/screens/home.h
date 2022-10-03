#ifndef QTWORLD_HOME_H
#define QTWORLD_HOME_H

#include <QWidget>
#include "user_profile.h"
#include "header.h"
#include "navigation.h"
#include "main_navigation.h"
#include "QEvent"

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

    bool eventFilter(QObject *, QEvent *) override;
    bool event(QEvent *) override;
    // to do
    void switchUserView();
    void switchAdminView();
    //

private slots:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Home *ui;
    Header *HeaderWidget;
    Navigation *NavigationWidget;
    MainNavigation *MainNavigationWidget;
    UserProfile *userProfile;

    MainButton *previousActiveMainButton = nullptr;
    ButtonDecorator *previousActiveButtonDecorator = nullptr;

    bool isAdminSwiched;
};

#endif
