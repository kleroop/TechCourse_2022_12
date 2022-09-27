//
// Created by child on 21/09/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_confirmation_modal.h"
// resolved

#include "confirmation_modal.h"

#include <utility>
#include "ui_confirmation_modal.h"

#include <QGraphicsDropShadowEffect>

ConfirmationModal::ConfirmationModal(QString _title, QString _message, QString _confirmLabel,
                                     ModalCallback _onConfirm, ModalCallback _onCancel,
                                     QWidget *parent)
    : QWidget(parent->window()),
      ui(new Ui::ConfirmationModal),
      title(std::move(_title)),
      message(std::move(_message)),
      confirmLabel(std::move(_confirmLabel)),
      onConfirm(std::move(_onConfirm)),
      onCancel(std::move(_onCancel))
{
    ui->setupUi(this);
    this->show();

    ui->modalTitle->setText(title);
    ui->modalContent->setText(message);
    ui->confirmButton->setText(confirmLabel);

    connect(ui->confirmButton, &QPushButton::clicked, this, [this]() {
        onConfirm();
        delete this;
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() {
        onCancel();
        delete this;
    });

    this->overlay = new ClickCatchOverlay(this, true);
    connect(overlay, &ClickCatchOverlay::clicked, this, [this]() { delete this; });

    auto *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(30);
    effect->setOffset(0, 0);
    effect->setColor("#999999");
    this->setGraphicsEffect(effect);

    this->move(parent->window()->width() / 2 - this->width() / 2,
               parent->window()->height() / 2 - this->height() / 2);

}

ConfirmationModal::~ConfirmationModal()
{
    delete overlay;
    delete ui;
}

void ConfirmationModal::onCall()
{
    this->show();
}
