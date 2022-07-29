#include "home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home)
{
    ui->setupUi(this);

    this->userProfileWidget = new userProfile(this);
    this->dropdownMenu = new userDropdown(this);
    dropdownMenu->hide();

    ui->userProfileLayout->replaceWidget(ui->profile, userProfileWidget);
    delete ui->profile;

    QObject::connect(userProfileWidget, &userProfile::dropdownButtonClicked, this, &Home::onDropdownButtonClicked);
}

Home::~Home()
{
    delete ui;
}

void Home::moveDropdown(){
    auto* button = userProfileWidget->findChild<QPushButton*>("dropdownButton");

    int dropdownX = button->x() + userProfileWidget->x() - dropdownMenu->width()/2 + button->width()/2;
    int dropdownY = button->y() + userProfileWidget->y() + button->height();
    dropdownMenu->move(dropdownX,  dropdownY);
}

void Home::onDropdownButtonClicked()
{
    if(dropdownMenu->isVisible()){
        dropdownMenu->hide();
    }else{
        dropdownMenu->show();
        moveDropdown();
    }
}

void Home::resizeEvent(QResizeEvent *event)
{
    moveDropdown();
    QWidget::resizeEvent(event);
}





