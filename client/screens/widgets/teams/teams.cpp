#include "teams.h"
#include "ui_Teams.h"

static const std::vector<std::string> locations{
    "",         "Alabama",         "Alaska",        "Arizona",  "Arkansas",  "California",
    "Colorado", "Connecticut",     "Delaware",      "Florida",  "Georgia",   "Hawaii",
    "Idaho",    "IllinoisIndiana", "Iowa",          "Kansas",   "Kentucky",  "Louisiana",
    "Maine",    "Maryland",        "Massachusetts", "Michigan", "Minnesota", "Mississippi",
    "Missouri", "Montana",         "Nebraska"
};

Teams::Teams(QWidget *parent) : QWidget(parent), ui(new Ui::Teams)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableWidget->verticalHeader()->setVisible(false);

    api.token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
                "eyJlbWFpbCI6ImFkbWluQGV4YW1wbGUuY29tIiwiaWF0IjoxNjYxMzcwNjcwLjExOCwic3ViIjoiYWRtaW"
                "4ifQ.E9AEDCWuVSrbPKS9CBeG0H4PD56tcqY4PhX5bMWnP4k";
    api.getCategories([=](const CategoriesTreeResponse &resp) {
        this->catTree = resp.categoriesTree;
        if (!catTree.categories.empty()) {
            init();
            fillTable();
        }
    });
    fillComboBox(ui->locCBox, locations);
    connect(ui->applyButton, &QPushButton::clicked, this, [this]() { applyChanges(); });
    connect(ui->catCBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &Teams::syncComboBox);
}

Teams::~Teams()
{
    delete ui;
}

void Teams::init()
{
    catTree.updateLists();
    fillComboBox(ui->catCBox, getNames(catTree.categories));
    syncComboBox(ui->catCBox->currentIndex());
    setEditingTeam(catTree.teams.back());
}

void Teams::fillTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(static_cast<int>(catTree.teams.size()));

    for (int row = 0; row < static_cast<int>(catTree.teams.size()); ++row) {
        auto team = catTree.teams[row];

        std::ostringstream dateAdded;
        dateAdded << std::put_time(&team->dateCreated, "%d/%m/%Y");

        ui->tableWidget->setItem(row, 0, new LeftAlignItem(QString::fromStdString(team->title)));
        ui->tableWidget->setItem(row, 1, new LeftAlignItem(QString::fromStdString(team->location)));
        ui->tableWidget->setItem(row, 2, new LeftAlignItem(QString::fromStdString(dateAdded.str())));
        ui->tableWidget->setItem(row, 3, new LeftAlignItem(QString::fromStdString(team->parent->title)));
        ui->tableWidget->setItem(row, 4, new LeftAlignItem(QString::fromStdString(team->parent->parent->title)));

        ui->tableWidget->setRowHeight(row, ui->tableWidget->rowHeight(row) + 15);
    }
}

void Teams::setEditingTeam(ICategory *team)
{
    activeTeam = team;

    ui->locCBox->setCurrentText(team->location.c_str());
    ui->catCBox->setCurrentText(team->parent->parent->title.c_str());
    syncComboBox(ui->catCBox->currentIndex());
    ui->subCBox->setCurrentText(team->parent->title.c_str());
    ui->teamNameForm->setText(QString::fromStdString(activeTeam->title));
}

void Teams::fillComboBox(QComboBox *box, std::vector<std::string> items, bool clean)
{
    QStringList list;
    if (clean)
        box->clear();
    for (const auto &item : items) {
        list.push_back(QString::fromStdString(item));
    }
    box->addItems(list);
}

void Teams::syncComboBox(int index)
{
    ICategory *active = &catTree.categories[index];
    fillComboBox(ui->subCBox, getNames(active->children));
}

std::vector<std::string> Teams::getNames(std::vector<ICategory *> categories)
{
    std::vector<std::string> names;
    for (auto cat : categories) {
        names.push_back(cat->title);
    }
    return names;
}

std::vector<std::string> Teams::getNames(std::vector<ICategory> categories)
{
    std::vector<std::string> names;
    for (auto cat : categories) {
        names.push_back(cat.title);
    }
    return names;
}

void Teams::applyChanges()
{
    std::string location_inbox = ui->locCBox->currentText().toStdString();
    std::string cat_inbox = ui->catCBox->currentText().toStdString();
    std::string sub_inbox = ui->subCBox->currentText().toStdString();
    std::string name_inbox = ui->teamNameForm->text().toStdString();

    activeTeam->location = location_inbox;
    activeTeam->title = name_inbox;

    if (!ui->subCBox->currentText().isEmpty()) {
        ICategory *activeCat = &catTree.categories[ui->catCBox->currentIndex()];
        ICategory *activeSub = &activeCat->children[ui->subCBox->currentIndex()];

        if (activeSub->title != activeTeam->parent->title) {
            ICategory *oldParent = activeTeam->parent;
            ICategory *newParent = activeSub;

            ptrdiff_t indexInParent = activeTeam - &oldParent->children[0];
            ICategory team = oldParent->children[indexInParent];

            oldParent->children.erase(oldParent->children.begin() + indexInParent);

            newParent->children.push_back(team);
            activeTeam = &newParent->children.back();
            activeTeam->parent = newParent;

            catTree.updateLists();
        }
    }

    fillTable();
}
