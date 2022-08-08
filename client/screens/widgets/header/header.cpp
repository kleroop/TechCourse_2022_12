#include "header.h"
#include "user_profile.h"
#include <ui_Header.h>

Header::Header(QWidget *parent, std::vector<QWidget *> right_widgets)
    : QWidget(parent), ui(new Ui::Header)
{
    ui->setupUi(this);
    widgets = right_widgets;
    for (auto w : widgets) {
        ui->right_menu->layout()->addWidget(w);
        w->setParent(this);
    }
    delete ui->profilePlaceholder;
    ui->right_menu->layout()->addWidget(new UserProfile(this));
}

Header::~Header()
{
    for (auto w : widgets) {
        delete w;
    }
    delete ui;
}

QHBoxLayout *Header::getRightSection()
{
    return ui->right_menu;
}
