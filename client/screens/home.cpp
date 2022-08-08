#include "home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);

    this->HeaderWidget = new Header(this);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);

    this->NavigationWidget = new Navigation(this);
    ui->localNavigation->replaceWidget(ui->navigationMock, NavigationWidget);
    delete ui->navigationMock;
}

Home::~Home() {
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}
