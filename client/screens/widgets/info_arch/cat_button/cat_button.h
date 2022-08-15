#ifndef QTWORLD_CAT_BUTTON_H
#define QTWORLD_CAT_BUTTON_H

#include <QWidget>
#include "QPushButton"
#include "../categories.h"


class CustomButton : public QPushButton {
Q_OBJECT

public:
    explicit CustomButton(QWidget *parent = nullptr, QPushButton *original = nullptr, ICategory *category = nullptr) {
        this->setParent(parent);
        this->setText(QString::fromStdString(category->title));
        this->setMinimumSize(original->minimumSize());
        this->setMaximumSize(original->maximumSize());
        this->setSizePolicy(original->sizePolicy());
        this->setStyleSheet(original->styleSheet());
        this->setCursor(original->cursor());
        this->category = category;
    };

    ICategory *category;
};


QT_BEGIN_NAMESPACE
namespace Ui { class CatButton; }
QT_END_NAMESPACE

class CatButton : public QWidget {
Q_OBJECT

public:
    explicit CatButton(QWidget *parent = nullptr, CustomButton* MainButton = nullptr);

    ~CatButton() override;

private:
    Ui::CatButton *ui;
};

#endif
