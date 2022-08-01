#include "user_profile.h"
#include "ui_user_profile.h"


UserProfile::UserProfile(QWidget *parent) : QWidget(parent), ui(new Ui::UserProfile) {
    ui->setupUi(this);

    this->dropdownMenu = new UserDropdown(parent, ui->dropdownButton, this);
    dropdownMenu->hide();

    connect(ui->dropdownButton, &QPushButton::clicked, dropdownMenu, &UserDropdown::onDropdownButtonClicked);
}

UserProfile::~UserProfile() {
    delete ui;
}