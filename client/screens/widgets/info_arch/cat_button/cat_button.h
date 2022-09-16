#ifndef QTWORLD_CAT_BUTTON_H
#define QTWORLD_CAT_BUTTON_H

#include <QWidget>
#include "QPushButton"
#include "../info_arch_dropdown/info_arch_dropdown.h"
#include "CustomButton.h"
#include "models/categories_model.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CatButton; }
QT_END_NAMESPACE

class CatButton : public QWidget {
Q_OBJECT

public:
    explicit CatButton(QWidget *parent, CustomButton *mainButton, bool active = false);

    ~CatButton() override;

    QPushButton* dropdownButton;

    bool isActive = false;

private:
    Ui::CatButton *ui;
    CustomButton* mainButton;
};

#endif