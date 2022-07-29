#include "user_profile.h"
#include "ui_user_profile.h"

userProfile::userProfile(QWidget *parent) : QWidget(parent), ui(new Ui::userProfile)
{
    ui->setupUi(this);

    connect(ui->dropdownButton, &QPushButton::clicked, this, &userProfile::onDropdownButtonClicked);
}

userProfile::~userProfile()
{
    delete ui;
}

void userProfile::onDropdownButtonClicked()
{
    emit dropdownButtonClicked();
}