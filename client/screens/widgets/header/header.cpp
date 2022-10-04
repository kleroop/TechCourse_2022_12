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

void Header::setSectionName(const QString &text)
{
    ui->sectionName->setText(text);
}

QWidget *Header::getScrollAreaWidget()
{
    return ui->scrollAreaWidget;
}

void Header::switchUserView()
{
    ui->categories->hide();
    ui->frame_3->hide();
}
void Header::switchAdminView()
{
    ui->categories->show();
    ui->frame_3->show();
}

QPushButton *Header::getSaveButton()
{
    return ui->saveButton;
}

QPushButton *Header::getRightScrollButton()
{
    return ui->rightScrollButton;
}

QPushButton *Header::getLeftScrollButton()
{
    return ui->leftScrollButton;
}

QFrame *Header::getCategories()
{
    return ui->categories;
}

QScrollArea *Header::getScrollArea()
{
    return ui->scrollArea;
}
