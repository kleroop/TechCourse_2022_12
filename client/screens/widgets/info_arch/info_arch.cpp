#include "info_arch.h"
#include "ui_info_arch.h"


CategoriesTree generateCat() {                                       //todo remove, only for testing
    std::vector<std::string> cats = {"NBA", "NFL", "MLB", "NHL"};

    CategoriesTree categories;

    for (const std::string &title: cats) {
        Category cat(0, title);
        std::vector<std::string> subcats(5, "sub" + title);
        for (const std::string &subtitle: subcats) {
            SubCategory sub(0, subtitle, &cat);
            std::vector<std::string> teams(5, "team" + subtitle);
            for (const std::string &teamtitle: teams) {
                Team team(0, teamtitle, &sub);
                sub.children.push_back(team);
            }
            cat.children.push_back(sub);
        }
        categories.categories.push_back(cat);
    }
    categories.categories.push_back(Category(0, "CBB"));

    return categories;
}


InfoArch::InfoArch(QWidget *parent) : QWidget(parent), ui(new Ui::InfoArch) {
    ui->setupUi(this);

    buttonTemplate = ui->buttonTemplate;

    buttonTemplate->setVisible(false);
    ui->categoriesFrame->layout()->takeAt(ui->categoriesFrame->layout()->indexOf(buttonTemplate));

    this->catTree = generateCat();

    fillContainer(ui->categoriesFrame->layout(), catTree.categories);

    auto* dropdown = new InfoArchDropdown(this);
}

InfoArch::~InfoArch() {
    delete ui;
}

std::vector<CatButton *> InfoArch::btnWrapper(std::vector<CustomButton *> buttons){
    std::vector<CatButton *> result;

    for(CustomButton* btn: buttons){
        result.push_back(new CatButton(this, btn));
    }

    return result;
}

std::vector<CustomButton *>
InfoArch::getCustomButtons(const std::vector<ICategory> &categories, QPushButton *btnTemplate, bool clickable) {
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

void clearLayout(QLayout *container) {  //todo move to utils
    QLayoutItem *item;
    while ((item = container->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void InfoArch::fillContainer(QLayout *container, const std::vector<ICategory> &categories, bool clickable,
                             bool replace) {//todo maybe move to utils
    std::vector<CustomButton *> buttons = getCustomButtons(categories, buttonTemplate, clickable);
    std::vector<CatButton *> wrappedButtons = btnWrapper(buttons);

    if (replace) {
        clearLayout(container);
    }

    for (QWidget *button: wrappedButtons) {
        container->addWidget(button);
    }
}

void InfoArch::buttonHandler(CustomButton *button) {
    ICategory *category = button->category;

    if (category->type == categoryTypes::CATEGORY) {
        clearLayout(ui->teamsFrame->layout());
        fillContainer(ui->subCategoriesFrame->layout(), category->children);
    } else if (category->type == categoryTypes::SUBCATEGORY) {
        fillContainer(ui->teamsFrame->layout(), category->children, false);
    }
}




















