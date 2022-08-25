#include "main_button.h"
#include "ui_main_button.h"
#include <QHoverEvent>

MainButton * activeMainButton = nullptr;

MainButton::MainButton(QWidget *parent, Header *header, const QString& text) : QPushButton(parent), ui(new Ui::MainButton)
{
    ui->setupUi(this);

    this->text = text;
    this->setText(text);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->show();
    this->header = header;
}

MainButton::~MainButton()
{
    delete ui;
}
bool MainButton::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::MouseButtonPress:
        mouseButtonPress(dynamic_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}
void MainButton::mouseButtonPress(QHoverEvent *event)
{
    if (activeMainButton && activeMainButton != this) activeMainButton->setDefaultStyleSheet();
    if (activeMainButton != this)
    {
        activeMainButton = this;
        header->setSectionName(text);
        this->setActiveStyleSheet();
    }
}


void MainButton::setDefaultStyleSheet()
{
    this->setStyleSheet("QPushButton{\n"
                        "font-family: 'Open Sans';\n"
                        "color: #B2B2B2;\n"
                        "font-weight: 500;\n"
                        "font-size: 18px;\n"
                        "border: none;\n"
                        "text-transform: uppercase;\n"
                        "}\n"
                        "QPushButton::hover{\n"
                        "color: #D72130;\n"
                        "}");
}
void MainButton::setActiveStyleSheet()
{
    this->setStyleSheet("QPushButton{\n"
                        "font-family: 'Open Sans';\n"
                        "color: #D72130;\n"
                        "font-weight: 500;\n"
                        "font-size: 18px;\n"
                        "border: none;\n"
                        "text-transform: uppercase;\n"
                        "}\n");
}
