#include "user_dropdown.h"
#include "ui_user_dropdown.h"


UserDropdown::UserDropdown(QWidget *parent) : QWidget(parent->window()), ui(new Ui::UserDropdown) {
    ui->setupUi(this);

    this->hide();

    auto *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor("#999999");
    this->setGraphicsEffect(effect);
}

UserDropdown::~UserDropdown() {
    delete ui;
}

void UserDropdown::updatePos(QPushButton* button) {
    int dropdownX = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).x() - this->width() / 2;
    int dropdownY = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).y() + button->height();
    this->move(dropdownX, dropdownY);
}

void UserDropdown::onDropdownButtonClicked(QPushButton* button) {
    if (this->isVisible()) {
        this->hide();
    } else {
        this->show();
        updatePos(button);
    }
}








