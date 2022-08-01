#include "user_login.h"
#include "ui_user_login.h"

UserLogin::UserLogin(QWidget *parent) : QWidget(parent), ui(new Ui::UserLogin) {
    ui->setupUi(this);

    //connect(ui->dropdownButton, &QPushButton::clicked, this, &userProfile::onDropdownButtonClicked);
}

UserLogin::~UserLogin() {
    delete ui;
}
//
//void userLogin::onDropdownButtonClicked()
//{
//    emit dropdownButtonClicked();
//}