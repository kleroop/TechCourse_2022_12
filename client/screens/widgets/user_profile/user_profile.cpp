#include "user_profile.h"
#include "ui_user_profile.h"


UserProfile::UserProfile(QWidget *parent) : QWidget(parent), ui(new Ui::UserProfile) {
    ui->setupUi(this);

    this->DropdownMenu = new UserDropdown(parent->parentWidget(), ui->dropdownButton, this);
    DropdownMenu->hide();

    connect(ui->dropdownButton, &QPushButton::clicked, DropdownMenu, &UserDropdown::onDropdownButtonClicked);
}

UserProfile::~UserProfile() {
    delete ui;
}
