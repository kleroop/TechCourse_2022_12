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
    explicit MainNavigation(QWidget *parent = nullptr, Header *header = nullptr,
                            bool _isAdminSwiched = true);
    ~MainNavigation() override;

    MainButton *addNewButton(const QString &text, bool isHidden);

    QVector<MainButton *> getMainButtonVector();
    void updateCategoriesAdminView();
    void updateCategoriesUserView();
    QVector<MainButton *> mainButtonVector;

    int scrollPosition;

private:
    Ui::MainNavigation *ui;
    Api api;
    CategoriesTree catTree;
    //    void deleteButton(MainButton* mainButton);
    Header *header;
    bool isAdminSwiched;
};

#endif // QTWORLD_MAIN_NAVIGATION_H
