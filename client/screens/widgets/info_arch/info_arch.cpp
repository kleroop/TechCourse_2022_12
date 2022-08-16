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
    buttonTemplate->hide();
    ui->categoriesFrame->layout()->takeAt(ui->categoriesFrame->layout()->indexOf(buttonTemplate));

    this->catTree = generateCat();
    this->dropdown = new InfoArchDropdown(this);

    fillCategories();

    connect(ui->addCategoryButton, &QPushButton::clicked, this, [this](){ createHandler(CategoryTypes::CATEGORY);});
    connect(ui->addSubCategoryButton, &QPushButton::clicked, this, [this](){ createHandler(CategoryTypes::SUBCATEGORY);});
    connect(ui->addTeamButton, &QPushButton::clicked, this, [this](){ createHandler(CategoryTypes::TEAM);});
}

InfoArch::~InfoArch() {
    delete ui;
}

std::vector<CatButton *> InfoArch::btnWrapper(const std::vector<CustomButton *>& buttons){
    std::vector<CatButton *> result;

    for(CustomButton* btn: buttons){
        result.push_back(new CatButton(this, btn, this->dropdown));
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

void InfoArch::fillCategories() {
    this->activeCategory = nullptr;
    clearLayout(ui->subCategoriesFrame->layout());
    clearLayout(ui->teamsFrame->layout());
    ui->addSubCategoryButton->hide();
    ui->addTeamButton->hide();
    fillContainer(ui->categoriesFrame->layout(), catTree.categories);
}

void InfoArch::fillSubCategories() {
    ICategory *category = this->activeCategory;
    this->activeSubCategory = nullptr;
    clearLayout(ui->teamsFrame->layout());
    ui->addSubCategoryButton->show();
    ui->addTeamButton->hide();
    fillContainer(ui->subCategoriesFrame->layout(), category->children);
}

void InfoArch::fillTeams() {
    ICategory *category = this->activeSubCategory;
    ui->addTeamButton->show();
    fillContainer(ui->teamsFrame->layout(), category->children, false);
}

void InfoArch::fillContainer(QLayout *container, const std::vector<ICategory> &categories, bool clickable, bool replace) {//todo maybe move to utils
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
        this->activeCategory = category;
        fillSubCategories();
    } else if (category->type == CategoryTypes::SUBCATEGORY) {
        this->activeSubCategory = category;
        fillTeams();
    }
}

void InfoArch::createHandler(CategoryTypes type) {
    this->addCatDialog = new AddCatDialog(this);

    addCatDialog->onCreateCall([=](const std::string &name) {
        if(!name.empty()){
            if(type == CategoryTypes::CATEGORY){
                this->catTree.categories.insert(catTree.categories.begin(), Category(NAN, name));
                fillCategories();
            }else if(type == CategoryTypes::SUBCATEGORY){
                this->activeCategory->children.insert(activeCategory->children.begin(), SubCategory(NAN, name));
                fillSubCategories();
            }else if(type == CategoryTypes::TEAM){
                this->activeSubCategory->children.insert(activeSubCategory->children.begin(), Team(NAN, name));
                fillTeams();
            }
        }
    });
}


























