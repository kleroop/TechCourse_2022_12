#include "header.h"
#include <ui_Header.h>

Header::Header(QWidget *parent) : QWidget(parent), ui(new Ui::Header)
{
    ui->setupUi(this);

    this->UserProfileWidget = new UserProfile(this);
    delete ui->profile_placeholder;
    ui->right_menu->layout()->addWidget(UserProfileWidget);
}

Header::~Header()
{
    delete ui;
}

QFrame *Header::getRightSection()
{
    return ui->right_menu;
}
