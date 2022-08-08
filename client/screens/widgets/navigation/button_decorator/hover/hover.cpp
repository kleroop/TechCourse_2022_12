#include "hover.h"
#include "ui_Hover.h"

Hover::Hover(QWidget *parent, QPushButton *hoverButton, QWidget *ParentWidget, const QString& text) : QWidget(parent), ui(new Ui::Hover)
{
    ui->setupUi(this);

    this->text = text;
    this->ParentWidget = ParentWidget;
    this->hoverButton = hoverButton;

    setPos();
    setHoverText();
}

Hover::~Hover()
{
    delete ui;
}
void Hover::setHoverText()
{
    int w = text.size() * 6;
    if (w < 150) w += 25;
    ui->label->setFixedSize(w, ui->label->height());
    ui->label->setText(text);
}
void Hover::setPos()
{
    int p_x = hoverButton->x() + hoverButton->width() + 21;
    int p_y = hoverButton->y() + ParentWidget->y() + (hoverButton->height() - this->height()) / 2;
    this->move(p_x, p_y);
}
