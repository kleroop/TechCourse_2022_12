#include "home.h"
#include "ui_Home.h"
#include <user_profile.h>

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);

<<<<<<< Updated upstream
    this->HeaderWidget = new Header(this);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);
=======
    this->UserProfileWidget = new UserProfile(this);
    ui->userProfileLayout->replaceWidget(ui->profile, UserProfileWidget);
    delete ui->profile;

    this->navigation = new Navigation(this);
    ui->localNavigation->replaceWidget(ui->navigationMock, navigation);
    delete ui->navigationMock;
>>>>>>> Stashed changes
}

Home::~Home() {
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
<<<<<<< Updated upstream
}



=======
    this->UserProfileWidget->dropdownMenu->updatePos(); //todo resize event doesnt trigger child's resize event slot, fbs
}
>>>>>>> Stashed changes
