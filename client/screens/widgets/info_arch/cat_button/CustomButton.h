#ifndef QTWORLD_CUSTOMBUTTON_H
#define QTWORLD_CUSTOMBUTTON_H

#include <QWidget>
#include "QPushButton"
#include "models/categories_model.h"

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

#endif
