#include "header.h"
#include <ui_Header.h>

Header::Header(QWidget *parent, std::vector<QWidget *> right_widgets)
    : QWidget(parent), ui(new Ui::Header)
{
    ui->setupUi(this);
    for (auto w : right_widgets) {
        ui->right_menu->layout()->addWidget(w);
        w->setParent(this);
    }
    delete ui->profilePlaceholder;
}

Header::~Header()
{
    delete ui;
}

QHBoxLayout *Header::getRightSection()
{
    return ui->right_menu;
}
