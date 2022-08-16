#ifndef QTWORLD_USER_DROPDOWN_H
#define QTWORLD_USER_DROPDOWN_H

#include <QWidget>
#include "QPushButton"
#include "QGraphicsDropShadowEffect"

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserDropdown;
}
QT_END_NAMESPACE

class UserDropdown : public QWidget {
Q_OBJECT

public:
    explicit UserDropdown(QWidget *parent = nullptr);

    ~UserDropdown() override;

    void updatePos(QPushButton* button);

public slots:

    void onDropdownButtonClicked(QPushButton* button);

private:
    Ui::UserDropdown *ui;
};

#endif
