#include "main_button.h"
#include "ui_main_button.h"
#include <QMouseEvent>

MainButton *activeMainButton = nullptr;
bool clickedActiveButton = false;

MainButton::MainButton(QWidget *parent, Header *header, const QString &text, bool isHidden)
    : QPushButton(parent), ui(new Ui::MainButton)
{
    ui->setupUi(this);

    this->isHidden = isHidden;
    this->text = text;
    this->header = header;
    this->setFixedWidth(text.size() * 12 + 40);
    this->setText(this->text);
    if (isHidden)
        this->hide();
    else
        this->show();
}

MainButton::~MainButton()
{
    delete ui;
}
bool MainButton::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
        mouseButtonPress();
        return true;
    default:
        break;
    }
    return QPushButton::event(e);
}

void MainButton::mouseButtonPress()
{
    if (activeMainButton && activeMainButton != this)
        activeMainButton->setDefaultStyleSheet();
    if (activeMainButton != this) {
        activeMainButton = this;
        header->setSectionName(text);
        this->setActiveStyleSheet();
        clickedActiveButton = true;
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
                        "text-align: left;\n"
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
                        "text-align: left;\n"
                        "}\n");
}
