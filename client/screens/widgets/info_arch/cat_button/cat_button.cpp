#include "cat_button.h"
#include "ui_cat_button.h"

CatButton::CatButton(QWidget *parent, CustomButton* mainButton, InfoArchDropdown* dropdown) : QWidget(parent), ui(new Ui::CatButton) {
    ui->setupUi(this);
    delete ui->buttonTemplate;
    ui->buttonContainer->addWidget(mainButton);

    this->mainButton = mainButton;
    this->dropdownButton = ui->dropdownButton;

    if(this->mainButton->category->isHidden){
        this->setStyleSheet(this->styleSheet() + "background-color: rgb(190, 190, 190);");
        this->mainButton->setStyleSheet(this->mainButton->styleSheet() + "color: rgb(255, 255, 255);");
    }
}

CatButton::~CatButton() {
    delete ui;
}

