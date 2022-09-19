#ifndef QTWORLD_INFO_ARCH_H
#define QTWORLD_INFO_ARCH_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"
#include "QPainter"

#include "cat_button.h"
#include "info_arch_dropdown.h"
#include "add_cat_window.h"
#include "api.h"
#include "models/categories_model.h"
#include "uiUtils.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class InfoArch;
}
QT_END_NAMESPACE

class InfoArch : public QWidget
{
    Q_OBJECT

public:
    explicit InfoArch(QWidget *parent = nullptr);

    ~InfoArch() override;

    InfoArchDropdown *dropdown;

public slots:
    void buttonHandler(CustomButton *but);
    void createHandler(CategoryTypes type);
    void hideCatHandler(ICategory *category, QPushButton *button);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::InfoArch *ui;
    Api api;

    CategoriesTree catTree;
    QPushButton *buttonTemplate;
    AddCatDialog *addCatDialog;

    ICategory *activeCategory = nullptr;
    ICategory *activeSubCategory = nullptr;

    void fillCategories(bool clean = true);
    void fillSubCategories();
    void fillTeams();

    void fillContainer(QLayout *container, const std::vector<ICategory> &categories,
                       bool clickable = true, bool replace = true);

    std::vector<CustomButton *> getCustomButtons(const std::vector<ICategory> &categories,
                                                 QPushButton *buttonTemplate,
                                                 bool clickable = true);

    std::vector<CatButton *> btnWrapper(const std::vector<CustomButton *> &buttons);

    void updateAllContainers();

    void LineDrawer(QLayout *leftContainer, QLayout *rightContainer, ICategory *category);

    void setActiveCat(ICategory *category);

    void setActiveSubCat(ICategory *category);
};

#endif
