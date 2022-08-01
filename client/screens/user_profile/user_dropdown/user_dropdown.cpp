#include "user_dropdown.h"
#include "ui_user_dropdown.h"

#include "QGraphicsDropShadowEffect"

UserDropdown::UserDropdown(QWidget *parent, QPushButton *DropdownButton,
                           QWidget *ButtonParent) : QWidget(parent), ui(new Ui::UserDropdown) {
    ui->setupUi(this);

    auto *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor("#999999");

    this->setGraphicsEffect(effect);

    this->DropdownButton = DropdownButton;
    this->ButtonParent = ButtonParent;
}

UserDropdown::~UserDropdown() {
    delete ui;
}

void UserDropdown::updatePos() {
    auto *button = this->DropdownButton;

    int dropdownX = button->x() + ButtonParent->x() - this->width() / 2 + button->width() / 2;
    int dropdownY = button->y() + ButtonParent->y() + button->height();
    this->move(dropdownX, dropdownY);
}

void UserDropdown::onDropdownButtonClicked() {
    if (this->isVisible()) {
        this->hide();
    } else {
        this->show();
        updatePos();
    }
}
