#ifndef QTWORLD_USER_DROPDOWN_H
#define QTWORLD_USER_DROPDOWN_H

#include <QWidget>
#include "QPushButton"

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

    void onDropdownButtonClicked(QPushButton* button);

private:
    Ui::InfoArchDropdown *ui;
};

#endif
