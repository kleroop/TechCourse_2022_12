#ifndef QTWORLD_INFO_ARCH_H
#define QTWORLD_INFO_ARCH_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"

#include "categories.h"


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
namespace Ui {
    class InfoArch;
}
QT_END_NAMESPACE

class InfoArch : public QWidget {
Q_OBJECT

public:
    explicit InfoArch(QWidget *parent = nullptr);

    ~InfoArch() override;

public slots:

    void buttonHandler(CustomButton *but);

private:
    Ui::InfoArch *ui;

    CategoriesTree catTree;
    QPushButton *buttonTemplate;

    void fillContainer(QLayout *container, const std::vector<ICategory> &categories, bool clickable = true,
                       bool replace = true);

    std::vector<CustomButton *>
    getCustomButtons(const std::vector<ICategory> &categories, QPushButton *buttonTemplate, bool clickable = true);
};

#endif
