#include "user_dropdown.h"
#include "ui_user_dropdown.h"

#include "QGraphicsDropShadowEffect"

UserDropdown::UserDropdown(QWidget *parent, QPushButton *DropdownButton,
                           QWidget *ButtonParent) : QWidget(parent), ui(new Ui::UserDropdown) {
    ui->setupUi(this);

    auto *effect = new QGraphicsDropShadowEffect(this);
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

    int dropdownX = (button->x() + button->width() / 2) - this->width() / 2 + ButtonParent->parentWidget()->x();// todo kill it, please
    int dropdownY = (button->y() + button->height() / 2) + button->height() + ButtonParent->parentWidget()->y();
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
