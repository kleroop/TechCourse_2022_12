#ifndef QTWORLD_INFO_ARCH_DROPDOWN_H
#define QTWORLD_INFO_ARCH_DROPDOWN_H

#include <QWidget>
#include "QPushButton"
#include "QGraphicsDropShadowEffect"
#include "../cat_button/CustomButton.h"
#include <click_catch_overlay.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class InfoArchDropdown;
}
QT_END_NAMESPACE

class InfoArchDropdown : public QWidget {
Q_OBJECT

public:
    explicit InfoArchDropdown(QWidget *parent = nullptr);

    ~InfoArchDropdown() override;

    void updatePos(QPushButton* button);

    void onCreateCall(bool isHidden, QPushButton *dropdownButton, const std::function<void()> &f);

private:
    ClickCatchOverlay* overlay;

    Ui::InfoArchDropdown *ui;

};

#endif
