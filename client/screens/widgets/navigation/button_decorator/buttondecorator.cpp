#include "buttondecorator.h"

#include <utility>
#include "ui_ButtonDecorator.h"

ButtonDecorator *activeButtonDecorator = nullptr;

ButtonDecorator::ButtonDecorator(QWidget *parent) : QPushButton(parent), ui(new Ui::ButtonDecorator)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
}

ButtonDecorator::~ButtonDecorator()
{
    if (hover)
        delete hover;
    delete ui;
}

bool ButtonDecorator::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::HoverEnter:
        hoverEnter();
        return true;
    case QEvent::HoverLeave:
        hoverLeave();
        return true;
    case QEvent::MouseButtonPress:
        mouseButtonPress();
        return true;
    default:
        break;
    }
    return QPushButton::event(e);
}

void ButtonDecorator::hoverEnter()
{
    hover = new Hover(parentWidget, this, this->parent, text);
    hover->show();
    this->setStyleSheet("border-radius: 27%;\n"
                        "padding: 13px;\n"
                        "background: #f9f9fb;\n"
                        "image: url(:/Resources/navigation_icons/"
                        + this->icon + "_icon_active.png);\n");
}

void ButtonDecorator::hoverLeave()
{
    if (hover)
        hover->hide();
    if (activeButtonDecorator == this) {
        this->setStyleSheet("border-radius: 27%;\n"
                            "padding: 13px;\n"
                            "background-color: none;\n"
                            "image: url(:/Resources/navigation_icons/"
                            + this->icon + "_icon_active.png);\n");
    } else {
        this->setStyleSheet("border-radius: 27%;\n"
                            "padding: 13px;\n"
                            "background-color: none;\n"
                            "image: url(:/Resources/navigation_icons/"
                            + this->icon + "_icon.png);\n");
    }
}

void ButtonDecorator::mouseButtonPress()
{
    if (activeButtonDecorator && activeButtonDecorator != this)
        activeButtonDecorator->setDefaultStyleSheet();
    if (activeButtonDecorator != this) {
        activeButtonDecorator = this;
        header->setSectionName(text);
    }
}

void ButtonDecorator::setData(QWidget *parent, Header *header, QWidget *parentWidget, QString text,
                              QString icon)
{
    this->parent = parent;
    this->parentWidget = parentWidget;
    this->text = std::move(text);
    this->icon = std::move(icon);
    this->header = header;
}
void ButtonDecorator::setDefaultStyleSheet()
{
    this->setStyleSheet("border-radius: 27%;\n"
                        "padding: 13px;\n"
                        "background-color: none;\n"
                        "image: url(:/Resources/navigation_icons/"
                        + this->icon + "_icon.png);\n");
}
