#include "add_cat_window.h"
#include "ui_add_cat_window.h"


AddCatDialog::AddCatDialog(QWidget *parent) : QWidget(parent->window()), ui(new Ui::AddCatDialog) {
    ui->setupUi(this);
    this->show();

    this->overlay = new ClickCatchOverlay(this, true);
    connect(overlay, &ClickCatchOverlay::clicked, this, [this](){delete this;});

    auto *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(30);
    effect->setOffset(0, 0);
    effect->setColor("#999999");
    this->setGraphicsEffect(effect);

    this->move(parent->window()->width()/2 - this->width()/2, parent->window()->height()/2 - this->height()/2);
}

AddCatDialog::~AddCatDialog() {
    delete overlay;
    delete ui;
}

void AddCatDialog::onCreateCall(const std::function<void(std::string)> &f) {
    this->show();
    ui->nameForm->setText("");

    connect(ui->cancelButton, &QPushButton::clicked, [this, f](){
        f("");
        delete this;
    });

    connect(ui->addButton, &QPushButton::clicked, [this, f](){
        f(ui->nameForm->text().toStdString());
        delete this;
    });
}


