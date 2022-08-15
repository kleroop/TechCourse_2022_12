#ifndef QTWORLD_INFO_ARCH_H
#define QTWORLD_INFO_ARCH_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"

#include "categories.h"
#include "cat_button.h"
#include "info_arch_dropdown.h"

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

    std::vector<CatButton *> btnWrapper(std::vector<CustomButton *> buttons);
};

#endif
