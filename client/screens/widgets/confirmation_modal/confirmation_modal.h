//
// Created by child on 21/09/2022.
//

#ifndef QTWORLD_CONFIRMATION_MODAL_H
#define QTWORLD_CONFIRMATION_MODAL_H

#include <QWidget>
#include "click_catch_overlay.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ConfirmationModal;
}
QT_END_NAMESPACE

typedef std::function<void()> ModalCallback;

class ConfirmationModal : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmationModal(QString _title, QString _message, QString _confirmLabel,
                               ModalCallback _onConfirm, ModalCallback _onCancel,
                               QWidget *parent = nullptr);
    ~ConfirmationModal() override;

private:
    QString title;
    QString message;
    QString confirmLabel;

    ModalCallback onConfirm;
    ModalCallback onCancel;

    ClickCatchOverlay *overlay{};
    Ui::ConfirmationModal *ui;
};

#endif // QTWORLD_CONFIRMATION_MODAL_H
