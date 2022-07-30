#include "user_dropdown.h"
#include "ui_user_dropdown.h"

#include "QGraphicsDropShadowEffect"

userDropdown::userDropdown(QWidget *parent) : QWidget(parent), ui(new Ui::userDropdown)
{
    ui->setupUi(this);

    auto *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor("#999999");

    this->setGraphicsEffect(effect);
}

userDropdown::~userDropdown()
{
    delete ui;
}
