#include "navigation.h"
#include "ui_Navigation.h"

Navigation::Navigation(QWidget *parent, Header* header) : QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    ui->surveysButton->setData(this, header, parent, "Surveys", "surveys");
    ui->bannersButton->setData(this, header, parent, "Banners", "banners");
    ui->languagesButton->setData(this, header, parent, "Languages", "languages");
    ui->footerButton->setData(this, header, parent, "Footer", "footer");
    ui->socialButton->setData(this, header, parent, "Social Networks", "social");
    ui->usersButton->setData(this, header, parent, "Users", "users");
    ui->architectureButton->setData(this, header, parent, "Information architecture", "architecture");
    ui->teamsButton->setData(this, header, parent, "Teams", "teams");
    ui->partnersButton->setData(this, header, parent, "News Partners", "partners");
    ui->advertisingButton->setData(this, header, parent, "Advertising", "advertising");
}

Navigation::~Navigation()
{
    delete ui;
}