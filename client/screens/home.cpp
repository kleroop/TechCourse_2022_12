#include "home.h"
#include "ui_Home.h"
#include <user_profile.h>

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
}



