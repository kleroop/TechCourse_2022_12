#include "teams.h"
#include "ui_Teams.h"

static const std::vector<std::string> locations{
        "",
        "Alabama",
        "Alaska",
        "Arizona",
        "Arkansas",
        "California",
        "Colorado",
        "Connecticut",
        "Delaware",
        "Florida",
        "Georgia",
        "Hawaii",
        "Idaho",
        "IllinoisIndiana",
        "Iowa",
        "Kansas",
        "Kentucky",
        "Louisiana",
        "Maine",
        "Maryland",
        "Massachusetts",
        "Michigan",
        "Minnesota",
        "Mississippi",
        "Missouri",
        "Montana",
        "Nebraska"
};

Teams::Teams(QWidget *parent) : QWidget(parent), ui(new Ui::Teams) {
    ui->setupUi(this);

    api.token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluQGV4YW1wbGUuY29tIiwiaWF0IjoxNjYxMzcwNjcwLjExOCwic3ViIjoiYWRtaW4ifQ.E9AEDCWuVSrbPKS9CBeG0H4PD56tcqY4PhX5bMWnP4k";
    api.getCategories([=](const CategoriesTreeResponse &resp) {
        this->catTree = resp.categoriesTree;
        if (!catTree.categories.empty()){
            init();
            fillTable();
        }
    });
    fillComboBox(ui->locCBox, locations);
    connect(ui->applyButton, &QPushButton::clicked, this, [this]() { applyChanges(); });
}

Teams::~Teams() {
    delete ui;
}

void Teams::init() {
    catTree.getLists();
    setEditingTeam(catTree.teams.back());
}

void Teams::fillTable() {
    clearLayout(ui->tableFrame->layout());

    for (auto team : catTree.teams){
        auto* box = new QHBoxLayout(this);

        auto* name = new QLabel(QString::fromStdString(team->title));
        auto* loc = new QLabel(QString::fromStdString(team->location));
        auto* cat = new QLabel(QString::fromStdString(team->parent->parent->title));
        auto* sub = new QLabel(QString::fromStdString(team->parent->title));

        box->layout()->addWidget(name);
        box->layout()->addWidget(loc);
        box->layout()->addWidget(cat);
        box->layout()->addWidget(sub);

        auto * temp = new QWidget();
        temp->setLayout(box);

        ui->tableFrame->layout()->addWidget(temp);
    }
}

void Teams::setEditingTeam(ICategory *team) {
    activeTeam = team;

    ui->locCBox->setCurrentText(team->location.c_str());
    ui->catCBox->setCurrentText(team->parent->parent->title.c_str());

    fillComboBox(ui->catCBox, getNames(catTree.categories));
    fillComboBox(ui->subCBox, getNames(team->parent->parent->children));
    ui->subCBox->setCurrentText(team->parent->title.c_str());

    ui->teamNameForm->setText(QString::fromStdString(activeTeam->title));
}

void Teams::fillComboBox(QComboBox *box, std::vector<std::string> items, bool clean) {
    QStringList list;
    if (clean) box->clear();
    for (const auto& item : items){
        list.push_back(QString::fromStdString(item));
    }
    box->addItems(list);
}

std::vector<std::string> Teams::getNames(std::vector<ICategory *> categories) {
    std::vector<std::string> names;
    for (auto cat : categories){
        names.push_back(cat->title);
    }
    return names;
}

std::vector<std::string> Teams::getNames(std::vector<ICategory> categories) {
    std::vector<std::string> names;
    for (auto cat : categories){
        names.push_back(cat.title);
    }
    return names;
}

void Teams::applyChanges() {
    std::string location_inbox = ui->locCBox->currentText().toStdString();
    std::string cat_inbox = ui->catCBox->currentText().toStdString();
    std::string sub_inbox = ui->subCBox->currentText().toStdString();
    std::string name_inbox = ui->teamNameForm->text().toStdString();

    activeTeam->location = location_inbox;
    activeTeam->title = name_inbox;

    fillTable();
}


