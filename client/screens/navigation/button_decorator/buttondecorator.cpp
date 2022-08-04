#include "buttondecorator.h"

#include <utility>
#include "ui_ButtonDecorator.h"



ButtonDecorator::ButtonDecorator(QWidget *parent) : QPushButton(parent), ui(new Ui::ButtonDecorator)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
    this->hover = nullptr;
}

ButtonDecorator::~ButtonDecorator()
{
    delete ui;
}

bool ButtonDecorator::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(dynamic_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(dynamic_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

void ButtonDecorator::hoverEnter(QHoverEvent * event)
{
    hover = new Hover(parentWidget, this, this->parent, text);
    hover->show();
    this->setStyleSheet("border-radius: 32%;\n"
                        "padding: 14px;\n"
                        "width: 10px;\n"
                        "height: 10px;\n"
                        "background: #f9f9fb;\n"
                        "image: url(:/Resources/icons/" + this->icon  + "_icon_active.png);\n");
}

void ButtonDecorator::hoverLeave(QHoverEvent * event)
{
    hover->hide();
    this->setStyleSheet("border-radius: 32%;\n"
                        "padding: 14px;\n"
                        "width: 10px;\n"
                        "height: 10px;\n"
                        "background-color: none;\n"
                        "image: url(:/Resources/icons/" + this->icon  + "_icon.png);\n");

}
void ButtonDecorator::setDate(QWidget *parent, QWidget *parentWidget, QString text, QString icon)
{
    this->parent = parent;
    this->parentWidget = parentWidget;
    this->text = text;
    this->icon = icon;
}
