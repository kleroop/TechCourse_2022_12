#include "home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);

    this->HeaderWidget = new Header(this);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);
}

Home::~Home() {
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this->HeaderWidget->UserProfileWidget->DropdownMenu->updatePos(); //todo resize event doesnt trigger child's resize event slot, fbs
}



