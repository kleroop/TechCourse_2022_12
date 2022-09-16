#include "teams.h"
#include "ui_Teams.h"


Teams::Teams(QWidget *parent) : QWidget(parent), ui(new Ui::Teams) {
    ui->setupUi(this);
}

Teams::~Teams() {
    delete ui;
}
