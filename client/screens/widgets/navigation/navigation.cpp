#include "navigation.h"
#include "ui_Navigation.h"

Navigation::Navigation(QWidget *parent, Header *header) : QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    (buttonDecoratorArray[0] = ui->surveysButton)->setData(this, header, parent, "Surveys", "surveys");
    (buttonDecoratorArray[1] = ui->bannersButton)->setData(this, header, parent, "Banners", "banners");
    (buttonDecoratorArray[2] = ui->languagesButton)->setData(this, header, parent, "Languages", "languages");
    (buttonDecoratorArray[3] = ui->footerButton)->setData(this, header, parent, "Footer", "footer");
    (buttonDecoratorArray[4] = ui->socialButton)->setData(this, header, parent, "Social Networks", "social");
    (buttonDecoratorArray[5] = ui->usersButton)->setData(this, header, parent, "Users", "users");
    (buttonDecoratorArray[6] = ui->architectureButton)->setData(this, header, parent, "Information architecture", "architecture");
    (buttonDecoratorArray[7] = ui->teamsButton)->setData(this, header, parent, "Teams", "teams");
    (buttonDecoratorArray[8] = ui->partnersButton)->setData(this, header, parent, "News Partners", "partners");
    (buttonDecoratorArray[9] = ui->advertisingButton)->setData(this, header, parent, "Advertising", "advertising");

    // only for this time
    ui->teamsButton->mouseButtonPress();
    ui->teamsButton->hoverLeave();
}

Navigation::~Navigation()
{
    delete ui;
}
QWidget *Navigation::getMainNavigationWidget()
{
    return ui->mainNavigationWidget;
}
void Navigation::setHideButton()
{
    for (auto w: buttonDecoratorArray) {
        w->hide();
    }
    ui->line->hide();
}
void Navigation::setShowButton()
{
    for (auto w: buttonDecoratorArray) {
        w->show();
    }
    ui->line->show();
}
