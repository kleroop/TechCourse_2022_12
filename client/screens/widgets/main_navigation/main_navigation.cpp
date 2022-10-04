#include <QBoxLayout>
#include "main_navigation.h"
#include "ui_main_navigation.h"
#include "QBoxLayout"
#include <qnamespace.h>
//#include "../../../api/api.h"
//#include "../../../../common/models/categories_model.h"

MainNavigation::MainNavigation(QWidget *parent, Header *header, bool _isAdminSwiched) : QWidget(parent), ui(new Ui::MainNavigation)
{
    ui->setupUi(this);
    this->header = header;

//    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(this->layout());

    api.token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluQGV4YW1wbGUuY29tIiwiaWF0IjoxNjYxMzcwNjcwLjExOCwic3ViIjoiYWRtaW4ifQ.E9AEDCWuVSrbPKS9CBeG0H4PD56tcqY4PhX5bMWnP4k";
    isAdminSwiched = _isAdminSwiched;
    if (isAdminSwiched) updateCategoriesAdminView();
    else updateCategoriesUserView();
    scrollPosition = 0;
    this->show();

}

MainNavigation::~MainNavigation()
{
    delete ui;
}

MainButton* MainNavigation::addNewButton(const QString &text, bool isHidden)
{
    this->mainButtonVector.push_front(new MainButton(this, this->header, text, isHidden));
    if (!isAdminSwiched) this->setLayoutDirection(Qt::LeftToRight);
    return mainButtonVector[0];
}

QVector<MainButton *> MainNavigation::getMainButtonVector()
{
    return this->mainButtonVector;
}

void MainNavigation::updateCategoriesAdminView()
{
    if (!mainButtonVector.isEmpty())
    {
        for (auto w: mainButtonVector)
        {
            delete w;
        }
        mainButtonVector.clear();
    }

    api.getCategories([=](const CategoriesTreeResponse &resp){
        if (!this->layout()) auto layout = new QHBoxLayout(this);
        this->catTree = resp.categoriesTree;
        for (auto &cat: this->catTree.categories)
        {
            cat.type = CategoryTypes::CATEGORY;
            this->layout()->addWidget(addNewButton(QString::fromStdString(cat.title), cat.isHidden));
        }
    });
}

void MainNavigation::updateCategoriesUserView()
{
    if (!mainButtonVector.isEmpty())
    {
        for (auto w: mainButtonVector)
        {
            delete w;
        }
        mainButtonVector.clear();
    }

    api.getCategories([=](const CategoriesTreeResponse &resp){
        auto layout = new QVBoxLayout(this);
        this->layout()->setSpacing(20);
        //this->setLayout(new QVBoxLayout);
//        auto *layout = qobject_cast<QVBoxLayout*>(this->layout());
        this->catTree = resp.categoriesTree;
        for (auto &cat: this->catTree.categories)
        {
            cat.type = CategoryTypes::CATEGORY;
            layout->addWidget(addNewButton(QString::fromStdString(cat.title), cat.isHidden));
        }
    });
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