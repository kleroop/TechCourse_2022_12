#include "header.h"
#include <ui_Header.h>

Header::Header(QWidget *parent) : QWidget(parent), ui(new Ui::Header)
{
    ui->setupUi(this);
}

Header::~Header()
{
    delete ui;
}

QHBoxLayout *Header::getRightSection()
{
    return ui->right_menu;
}
