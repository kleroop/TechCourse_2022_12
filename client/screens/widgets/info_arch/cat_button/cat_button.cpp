#include "cat_button.h"
#include "ui_cat_button.h"

CatButton::CatButton(QWidget *parent, CustomButton* mainButton, InfoArchDropdown* dropdown) : QWidget(parent), ui(new Ui::CatButton) {
    ui->setupUi(this);
    delete ui->buttonTemplate;
    ui->buttonContainer->addWidget(mainButton);

    this->mainButton = mainButton;
    this->dropdown = dropdown;

    connect(ui->dropdownButton, &QPushButton::clicked, this->dropdown, [this]() {
        this->dropdown->onDropdownButtonClicked(ui->dropdownButton, this->mainButton);
    });
}

CatButton::~CatButton() {
    delete ui;
}

