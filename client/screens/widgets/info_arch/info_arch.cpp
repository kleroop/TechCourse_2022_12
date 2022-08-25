#include "info_arch.h"
#include "ui_info_arch.h"

InfoArch::InfoArch(QWidget *parent) : QWidget(parent), ui(new Ui::InfoArch) {
    //todo add scroll on category containers overflow
    ui->setupUi(this);

    buttonTemplate = ui->buttonTemplate;
    buttonTemplate->hide();
    ui->categoriesFrame->layout()->takeAt(ui->categoriesFrame->layout()->indexOf(buttonTemplate));


    api.token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluQGV4YW1wbGUuY29tIiwiaWF0IjoxNjYxMzcwNjcwLjExOCwic3ViIjoiYWRtaW4ifQ.E9AEDCWuVSrbPKS9CBeG0H4PD56tcqY4PhX5bMWnP4k";
    api.getCategories([=](const CategoriesTreeResponse &resp) {
        this->catTree = resp.categoriesTree;
        for (auto &cat: this->catTree.categories) {
            cat.type = CategoryTypes::CATEGORY;
            for (auto &scat: cat.children) {
                scat.type = CategoryTypes::SUBCATEGORY;
                scat.parent = &cat;
                for (auto &team: scat.children) {
                    team.type = CategoryTypes::TEAM;
                    team.parent = &scat;
                }
            }
        }
        fillCategories();
    });

    connect(ui->addCategoryButton, &QPushButton::clicked, this, [this]() { createHandler(CategoryTypes::CATEGORY); });
    connect(ui->addSubCategoryButton, &QPushButton::clicked, this,[this]() { createHandler(CategoryTypes::SUBCATEGORY); });
    connect(ui->addTeamButton, &QPushButton::clicked, this, [this]() { createHandler(CategoryTypes::TEAM); });
}

InfoArch::~InfoArch() {
    delete ui;
}

std::vector<CatButton *> InfoArch::btnWrapper(const std::vector<CustomButton *> &buttons) {
    std::vector<CatButton *> result;

    for (CustomButton *btn: buttons) {
        bool isActive = false;
        if (btn->category == this->activeCategory || btn->category == this->activeSubCategory) isActive = true;
        auto *tempButton = new CatButton(this, btn, isActive);
        connect(tempButton->dropdownButton, &QPushButton::clicked, this, [this, btn, tempButton] {
            this->hideCatHandler(btn->category, tempButton->dropdownButton);
        });
        result.push_back(tempButton);
    }

    return result;
}

std::vector<CustomButton *> InfoArch::getCustomButtons(const std::vector<ICategory> &categories, QPushButton *btnTemplate, bool clickable)
{
    std::vector<CustomButton *> result;

    for (const ICategory &category: categories) {
        auto *tempButton = new CustomButton(this, btnTemplate, (ICategory *) &category);

        if (clickable) {
            connect(tempButton, &QPushButton::clicked, this, [this, tempButton]() {
                buttonHandler(tempButton);
            });
        } else {
            tempButton->setCursor(Qt::ArrowCursor);
        }

        result.push_back(tempButton);
    }
    return result;
}

std::vector<QWidget *> getLayoutWidgets(QLayout *container) {  //todo move to utils
    QLayoutItem *item;
    std::vector<QWidget *> result;
    for (int i = 0; i < container->count(); i++) {
        item = container->itemAt(i);
        result.push_back(item->widget());
    }
    return result;
}

void clearLayout(QLayout *container) {  //todo move to utils
    QLayoutItem *item;
    while ((item = container->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void InfoArch::setActiveCat(ICategory *category) {
    this->activeCategory = category;
    setActiveSubCat(nullptr);
    clearLayout(ui->subCategoriesFrame->layout());
    clearLayout(ui->teamsFrame->layout());
    ui->addSubCategoryButton->hide();
    ui->addTeamButton->hide();
    fillCategories(false);
    fillSubCategories();
}

void InfoArch::setActiveSubCat(ICategory *category) {
    this->activeSubCategory = category;
    clearLayout(ui->teamsFrame->layout());
    ui->addTeamButton->hide();
    fillSubCategories();
    fillTeams();
}

void InfoArch::updateAllContainers() {
    fillCategories(false);
    fillSubCategories();
    fillTeams();
}

void InfoArch::fillCategories(bool clean) {
    if (clean) {
        setActiveCat(nullptr);
    }
    fillContainer(ui->categoriesFrame->layout(), catTree.categories);
    update();
}

void InfoArch::fillSubCategories() {
    ICategory *category = this->activeCategory;
    if (category) {
        ui->addSubCategoryButton->show();
        fillContainer(ui->subCategoriesFrame->layout(), category->children);
    }
    update();
}

void InfoArch::fillTeams() {
    ICategory *category = this->activeSubCategory;
    if (category) {
        ui->addTeamButton->show();
        fillContainer(ui->teamsFrame->layout(), category->children, false);
    }
    update();
}

void InfoArch::fillContainer(QLayout *container, const std::vector<ICategory> &categories, bool clickable,
                             bool replace) {//todo maybe move to utils
    std::vector<CatButton *> wrappedButtons = btnWrapper(getCustomButtons(categories, buttonTemplate, clickable));

    if (replace) {
        clearLayout(container);
    }

    for (QWidget *button: wrappedButtons) {
        container->addWidget(button);
    }
}

void InfoArch::buttonHandler(CustomButton *button) {
    ICategory *category = button->category;

    if (category->type == CategoryTypes::CATEGORY) {
        setActiveCat(category);
    } else if (category->type == CategoryTypes::SUBCATEGORY) {
        setActiveSubCat(category);
    }
    update();
}

void InfoArch::createHandler(CategoryTypes type) {
    this->addCatDialog = new AddCatDialog(this);

    addCatDialog->onCreateCall([=](const std::string &name) {
        if (!name.empty()) {
            if (type == CategoryTypes::CATEGORY) {
                this->catTree.categories.insert
                        (catTree.categories.begin(), Category(name, false, nullptr));
                //fillCategories();
            } else if (type == CategoryTypes::SUBCATEGORY) {
                this->activeCategory->children.insert
                        (activeCategory->children.begin(), SubCategory(name, false, this->activeCategory));
                //fillSubCategories();
            } else if (type == CategoryTypes::TEAM) {
                this->activeSubCategory->children.insert
                        (activeSubCategory->children.begin(), Team(name, false, this->activeSubCategory));
                //fillTeams();
            }
        }

        api.updateCategories(this->catTree, [=](const CategoriesTreeResponse &resp) {
            updateAllContainers();
        });
    });
}

void InfoArch::hideCatHandler(ICategory *category, QPushButton *button) {
    this->dropdown = new InfoArchDropdown(this);

    dropdown->onCreateCall(category->isHidden, button, [=]() {
        if (category->isHidden) {
            category->isHidden = false;
        } else {
            category->isHidden = true;
        }

        api.updateCategories(this->catTree, [=](const CategoriesTreeResponse &resp) {
            updateAllContainers();
        });
    });
}

void InfoArch::paintEvent(QPaintEvent *e) {
    LineDrawer(ui->categoriesFrame->layout(), ui->subCategoriesFrame->layout(), this->activeCategory);
    LineDrawer(ui->subCategoriesFrame->layout(), ui->teamsFrame->layout(), this->activeSubCategory);
}

void InfoArch::LineDrawer(QLayout *leftContainer, QLayout *rightContainer, ICategory *category) {
    if (category) {
        QPainter painter(this);
        QPen pen;
        pen.setWidth(1);
        pen.setStyle(Qt::DashLine);
        pen.setColor(QColor("#D4D9E2"));
        painter.setPen(pen);

        std::vector<QPoint> rightBtns;
        QPoint activeCat;
        int midX;

        std::vector<QWidget *> rightWidgets = getLayoutWidgets(rightContainer);
        std::vector<QWidget *> leftWidgets = getLayoutWidgets(leftContainer);

        if (!rightWidgets.empty() && !leftWidgets.empty()) {
            for (QWidget *w: rightWidgets) {
                rightBtns.emplace_back(w->mapTo(this, QPoint(0, 0)).x(),
                                       w->mapTo(this, QPoint(0, 0)).y() + w->height() / 2);
            }
            for (QWidget *w: leftWidgets)
                if (dynamic_cast<CatButton *>(w)->isActive) {
                    activeCat = QPoint(w->mapTo(this, QPoint(0, 0)).x() + w->width(),
                                       w->mapTo(this, QPoint(0, 0)).y() + w->height() / 2);
                };

            midX = abs(rightBtns.front().x() + activeCat.x()) / 2;


            painter.drawLine(activeCat, QPoint(midX, activeCat.y())); //horizontal from active cat
            painter.drawLine(midX, rightBtns.front().y(), midX, activeCat.y());  //vertical from first right to active

            if (rightBtns.back().y() > activeCat.y())
                painter.drawLine(midX, activeCat.y(), midX, rightBtns.back().y());  //vertical from last right to active

            for (QPoint p: rightBtns) {
                painter.drawLine(midX, p.y(), p.x(), p.y()); //horizontal from right btns
            }
        }
    }
}


























