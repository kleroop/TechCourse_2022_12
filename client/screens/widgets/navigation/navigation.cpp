#include "navigation.h"
#include "ui_Navigation.h"

Navigation::Navigation(QWidget *parent) : QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    ui->surveysButton->setData(this, parent, "Surveys", "surveys");
    ui->bannersButton->setData(this, parent, "Banners", "banners");
    ui->languagesButton->setData(this, parent, "Languages", "languages");
    ui->footerButton->setData(this, parent, "Footer", "footer");
    ui->socialButton->setData(this, parent, "Social Networks", "social");
    ui->usersButton->setData(this, parent, "Users", "users");
    ui->architectureButton->setData(this, parent, "Information architecture", "architecture");
    ui->teamsButton->setData(this, parent, "Teams", "teams");
    ui->partnersButton->setData(this, parent, "News Partners", "partners");
    ui->advertisingButton->setData(this, parent, "Advertising", "advertising");
}

Navigation::~Navigation()
{
    delete ui;
}