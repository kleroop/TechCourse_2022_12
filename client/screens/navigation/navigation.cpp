#include "navigation.h"
#include "ui_Navigation.h"

Navigation::Navigation(QWidget *parent) : QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    ui->surveysButton->setDate(this, parent, "Surveys", "surveys");
    ui->bannersButton->setDate(this, parent, "Banners", "banners");
    ui->languagesButton->setDate(this, parent, "Languages", "languages");
    ui->footerButton->setDate(this, parent, "Footer", "footer");
    ui->socialButton->setDate(this, parent, "Social", "social");
    ui->usersButton->setDate(this, parent, "Users", "users");
    ui->architectureButton->setDate(this, parent, "Architecture", "architecture");
    ui->teamsButton->setDate(this, parent, "Teams", "teams");
    ui->partnersButton->setDate(this, parent, "Partners", "partners");
    ui->advertisingButton->setDate(this, parent, "Advertising", "advertising");
}

Navigation::~Navigation()
{
    delete ui;
}