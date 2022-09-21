#include "click_catch_overlay.h"
#include "ui_click_catch_overlay.h"

ClickCatchOverlay::ClickCatchOverlay(QWidget *parent, bool blurred)
    : QWidget(parent->window()), ui(new Ui::ClickCatchOverlay)
{
    ui->setupUi(this);
    this->show();
    this->stackUnder(parent);
    this->setFixedSize(window()->size());

    if (blurred) {
        ui->button->setStyleSheet(ui->button->styleSheet()
                                  + "background-color: rgba(77, 75, 75, 0.4);");
    }

    connect(ui->button, &QPushButton::clicked, this, [this]() { emit clicked(); });
}

ClickCatchOverlay::~ClickCatchOverlay()
{
    delete ui;
}

void ClickCatchOverlay::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->setFixedSize(window()->size());
}
