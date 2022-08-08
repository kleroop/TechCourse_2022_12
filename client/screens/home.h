#ifndef QTWORLD_HOME_H
#define QTWORLD_HOME_H

#include <QWidget>
#include "widgets/header/header.h"
#include "widgets/navigation/navigation.h"
#include "widgets/user_profile/user_profile.h"

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

private slots:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Home *ui;
    Header *HeaderWidget;
    Navigation *NavigationWidget;
};

#endif
