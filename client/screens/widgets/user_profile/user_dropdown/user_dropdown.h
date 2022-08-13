#ifndef QTWORLD_USER_DROPDOWN_H
#define QTWORLD_USER_DROPDOWN_H

#include <QWidget>
#include "QPushButton"

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserDropdown;
}
QT_END_NAMESPACE

class UserDropdown : public QWidget {
Q_OBJECT

public:
    explicit UserDropdown(QWidget *parent = nullptr, QPushButton *DropdownButton = nullptr,
                          QWidget *ButtonParent = nullptr);

    ~UserDropdown() override;

    void updatePos();

public slots:

    void onDropdownButtonClicked();

private:
    Ui::UserDropdown *ui;
    QPushButton *DropdownButton;
    QWidget *ButtonParent;
};

#endif
