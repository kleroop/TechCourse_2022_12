#include "user_dropdown.h"
#include "ui_user_dropdown.h"

userDropdown::userDropdown(QWidget *parent) : QWidget(parent), ui(new Ui::userDropdown)
{
    ui->setupUi(this);
}

userDropdown::~userDropdown()
{
    delete ui;
}
