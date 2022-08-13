#include "home.h"
#include "ui_Home.h"

#include "info_arch.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home)
{
    ui->setupUi(this);

    this->HeaderWidget = new Header(this);
    auto prof = new UserProfile(this->HeaderWidget);
    this->HeaderWidget->getRightSection()->addWidget(prof);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);

    this->NavigationWidget = new Navigation(this);
    ui->localNavigation->replaceWidget(ui->navigationMock, NavigationWidget);
    delete ui->navigationMock;

    auto InfoArchWidget = new InfoArch(this);
    delete ui->contentMock;
    ui->contentContainer->layout()->addWidget(InfoArchWidget);
}

Home::~Home()
{
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
