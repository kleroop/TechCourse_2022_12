#include "cat_button.h"
#include "ui_cat_button.h"

CatButton::CatButton(QWidget *parent, CustomButton* MainButton) : QWidget(parent), ui(new Ui::CatButton) {
    ui->setupUi(this);
    delete ui->buttonTemplate;
    ui->buttonContainer->addWidget(MainButton);
}

CatButton::~CatButton() {
    delete ui;
}

