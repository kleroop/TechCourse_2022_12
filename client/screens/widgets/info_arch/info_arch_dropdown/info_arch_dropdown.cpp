#include "info_arch_dropdown.h"
#include "ui_info_arch_dropdown.h"

InfoArchDropdown::InfoArchDropdown(QWidget *parent)
    : QWidget(parent->window()), ui(new Ui::InfoArchDropdown)
{
    ui->setupUi(this);
    this->show();

    this->overlay = new ClickCatchOverlay(this);
    connect(overlay, &ClickCatchOverlay::clicked, this, [this]() { delete this; });

    auto *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(30);
    effect->setOffset(0, 0);
    effect->setColor("#999999");
    this->setGraphicsEffect(effect);
}

InfoArchDropdown::~InfoArchDropdown()
{
    delete overlay;
    delete ui;
}

void InfoArchDropdown::updatePos(QPushButton *button)
{
    int dropdownX = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).x();
    int dropdownY = button->mapTo(dynamic_cast<const QWidget *>(this->parent()), QPoint(0, 0)).y()
            + button->height();
    this->move(dropdownX, dropdownY);
}

void InfoArchDropdown::onCreateCall(bool isHidden, QPushButton *dropdownButton,
                                    const std::function<void()> &f)
{
    if (isHidden) {
        ui->hideButton->setText("Show");
    } else {
        ui->hideButton->setText("Hide");
    }

    updatePos(dropdownButton);

    connect(ui->hideButton, &QPushButton::clicked, [this, f]() {
        f();
        delete this;
    });
}
