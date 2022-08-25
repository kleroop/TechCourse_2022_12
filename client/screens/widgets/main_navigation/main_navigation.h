#ifndef QTWORLD_MAIN_NAVIGATION_H
#define QTWORLD_MAIN_NAVIGATION_H

#include <QWidget>
#include "main_button/main_button.h"
#include <QVector>
#include "../header/header.h"
#include "api.h"
#include "models/categories_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainNavigation;
}
QT_END_NAMESPACE

class MainNavigation : public QWidget
{
public:
    explicit MainNavigation(QWidget *parent = nullptr, Header *header = nullptr);
    ~MainNavigation() override;

    MainButton* addNewButton(const QString &text, bool isHidden);

    QVector<MainButton *> getMainButtonVector();
    void updateCategories();
    QVector<MainButton *> mainButtonVector;

    int scrollPosition = 0;

private:
    Ui::MainNavigation *ui;
    Api api;
    CategoriesTree catTree;
//    void deleteButton(MainButton* mainButton);
    Header *header;
};

#endif // QTWORLD_MAIN_NAVIGATION_H
