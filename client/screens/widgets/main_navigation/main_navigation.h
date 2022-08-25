#ifndef QTWORLD_MAIN_NAVIGATION_H
#define QTWORLD_MAIN_NAVIGATION_H

#include <QWidget>
#include "main_button/main_button.h"
#include <QVector>
#include "../header/header.h"

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

    void addNewButton(const QString &text);

    QVector<MainButton *> getMainButtonVector();

    void upDate();

//    void deleteButton(MainButton* mainButton);
private:
    QVector<MainButton *> mainButtonVector;
    Ui::MainNavigation *ui;
    Header *header;
};

#endif // QTWORLD_MAIN_NAVIGATION_H
