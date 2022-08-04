#ifndef QTWORLD_HOME_H
#define QTWORLD_HOME_H

#include <QWidget>
<<<<<<< Updated upstream
#include "widgets/header/header.h"
=======
#include "navigation/navigation.h"
#include "user_profile/user_profile.h"
>>>>>>> Stashed changes

QT_BEGIN_NAMESPACE
namespace Ui {
    class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);

    ~Home() override;
<<<<<<< Updated upstream

private slots:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Home *ui;

    Header *HeaderWidget;
=======
    void resizeEvent(QResizeEvent *event);
    Navigation *navigation;
    UserProfile *UserProfileWidget;
private:
    Ui::Home *ui;

>>>>>>> Stashed changes
};

#endif
