#include "home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);

    this->UserProfileWidget = new UserProfile(this);
    ui->userProfileLayout->replaceWidget(ui->profile, UserProfileWidget);
    delete ui->profile;
}

Home::~Home() {
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this->UserProfileWidget->dropdownMenu->updatePos(); //todo resize event doesnt trigger child's resize event slot, fbs
}



