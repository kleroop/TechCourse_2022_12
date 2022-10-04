#ifndef QTWORLD_NAVIGATION_H
#define QTWORLD_NAVIGATION_H

#include <QWidget>
#include "button_decorator/buttondecorator.h"
#include <QVector>
#include "api.h"
#include "models/categories_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Navigation;
}
QT_END_NAMESPACE

class Navigation : public QWidget
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = nullptr, Header* header = nullptr);
    ~Navigation() override;

    QWidget* getMainNavigationWidget();

    void setHideButton();
    void setShowButton();

    ButtonDecorator* buttonDecoratorArray[10];
private:
    Api api;
    CategoriesTree catTree;
    Ui::Navigation *ui;
};

#endif // QTWORLD_NAVIGATION_H
