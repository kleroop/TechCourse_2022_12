#include "buttondecorator.h"

#include <utility>
#include "ui_ButtonDecorator.h"



ButtonDecorator::ButtonDecorator(QWidget *parent) : QPushButton(parent), ui(new Ui::ButtonDecorator)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
}

ButtonDecorator::~ButtonDecorator()
{
    delete hover;
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
    this->setStyleSheet("border-radius: 27%;\n"
                        "padding: 13px;\n"
                        "background: #f9f9fb;\n"
                        "image: url(:/Resources/navigation_icons/" + this->icon  + "_icon_active.png);\n");
}

void ButtonDecorator::hoverLeave(QHoverEvent * event)
{
    hover->hide();
    this->setStyleSheet("border-radius: 27%;\n"
                        "padding: 13px;\n"
                        "background-color: none;\n"
                        "image: url(:/Resources/navigation_icons/" + this->icon  + "_icon.png);\n");

}
void ButtonDecorator::setData(QWidget *parent, QWidget *parentWidget, QString text, QString icon)
{
    this->parent = parent;
    this->parentWidget = parentWidget;
    this->text = std::move(text);
    this->icon = std::move(icon);
}
