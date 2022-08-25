#include "main_navigation.h"
#include "ui_main_navigation.h"
#include "QBoxLayout"

MainNavigation::MainNavigation(QWidget *parent, Header *header) : QWidget(parent), ui(new Ui::MainNavigation)
{
    ui->setupUi(this);
    this->header = header;

    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(this->layout());

    addNewButton("Home");
    addNewButton("NBA");
    addNewButton("NFL");

    for (auto w : mainButtonVector) {
        layout->addWidget(w);
    }

    this->show();

}

MainNavigation::~MainNavigation()
{
    delete ui;
}

void MainNavigation::addNewButton(const QString &text)
{
    this->mainButtonVector.push_front(new MainButton(this, this->header, text));
}
QVector<MainButton *> MainNavigation::getMainButtonVector()
{
    return this->mainButtonVector;
}

void MainNavigation::upDate()
{
    int a = 2;
}

//void MainNavigation::deleteButton(MainButton* mainButton)
//{
//    int length = mainButtonVector.length();
//    if (!length) return;
//
//    for (int i = 0; i < length; i++)
//    {
//        if (mainButtonVector[i] == mainButton)
//        {
//            mainButtonVector.removeAt(i);
//        }
//    }
//}
