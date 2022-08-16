#ifndef QTWORLD_INFO_ARCH_DROPDOWN_H
#define QTWORLD_INFO_ARCH_DROPDOWN_H

#include <QWidget>
#include "QPushButton"
#include "QGraphicsDropShadowEffect"
#include "../cat_button/CustomButton.h"

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

public slots:

    void onDropdownButtonClicked(QPushButton* dropdownButton, CustomButton* catButton);

private:
    Ui::InfoArchDropdown *ui;
};

#endif
