#include "hover.h"
#include "ui_Hover.h"

Hover::Hover(QWidget *parent, QPushButton *hoverButton, QWidget *ParentButton, const QString& text) : QWidget(parent), ui(new Ui::Hover)
{
    ui->setupUi(this);
    ui->label->setText(text);
    this->ParentButton = ParentButton;
    this->hoverButton = hoverButton;

    int p_x = hoverButton->x() + hoverButton->width() + 21;
    int p_y = hoverButton->y() + ParentButton->y() + 10;
    this->move(p_x, p_y);
}

Hover::~Hover()
{
    delete ui;
}
