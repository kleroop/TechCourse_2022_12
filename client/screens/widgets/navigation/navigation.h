#ifndef QTWORLD_NAVIGATION_H
#define QTWORLD_NAVIGATION_H

#include <QWidget>
#include "button_decorator/buttondecorator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Navigation;
}
QT_END_NAMESPACE

class Navigation : public QWidget
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = nullptr, Header *header = nullptr);
    ~Navigation() override;

    QWidget *getMainNavigationWidget();

    void setHideButton();
    void setShowButton();

private:
    Ui::Navigation *ui;
};

#endif // QTWORLD_NAVIGATION_H
