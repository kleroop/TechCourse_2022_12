#include "info_arch_dropdown.h"
#include "ui_info_arch_dropdown.h"

#include "QGraphicsDropShadowEffect"


InfoArchDropdown::InfoArchDropdown(QWidget *parent) : QWidget(parent->window()), ui(new Ui::InfoArchDropdown) {
    ui->setupUi(this);

    auto *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor("#999999");
    this->setGraphicsEffect(effect);
}

InfoArchDropdown::~InfoArchDropdown() {
    delete ui;
}

void InfoArchDropdown::updatePos(QPushButton* button) {
    int dropdownX = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).x() - this->width() / 2;
    int dropdownY = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).y() + button->height();
    this->move(dropdownX, dropdownY);
}

void InfoArchDropdown::onDropdownButtonClicked(QPushButton* button) {
    if (this->isVisible()) {
        this->hide();
    } else {
        this->show();
        updatePos(button);
    }
}








