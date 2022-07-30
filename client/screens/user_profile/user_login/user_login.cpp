#include "user_login.h"
#include "ui_user_login.h"

userLogin::userLogin(QWidget *parent) : QWidget(parent), ui(new Ui::userLogin)
{
    ui->setupUi(this);

    //connect(ui->dropdownButton, &QPushButton::clicked, this, &userProfile::onDropdownButtonClicked);
}

userLogin::~userLogin()
{
    delete ui;
}
//
//void userLogin::onDropdownButtonClicked()
//{
//    emit dropdownButtonClicked();
//}