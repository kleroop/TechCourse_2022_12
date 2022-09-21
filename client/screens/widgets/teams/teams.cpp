#include "teams.h"
#include "ui_Teams.h"

static const std::vector<std::string> locations{
        "", "Alabama", "Alaska", "Arizona", "Arkansas", "California",
        "Colorado", "Connecticut", "Delaware", "Florida", "Georgia", "Hawaii",
        "Idaho", "IllinoisIndiana", "Iowa", "Kansas", "Kentucky", "Louisiana",
        "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi",
        "Missouri", "Montana", "Nebraska"
};

static const QString EditButtonStyle = "background: transparent;\n"
                                       "color: rgb(215, 33, 48);\n"
                                       "font: 50 12pt \"Open Sans\";";

static const QString DeleteButtonStyle = "background-color: transparent;\n"
                                         "qproperty-icon: url(\" \"); /* empty image */\n"
                                         "qproperty-iconSize: 21px 21px;\n"
                                         "background-image: url(:/Resources/trash_icon.png);\n"
                                         "background-repeat: no-repeat;\n"
                                         "background-position: center center;";

Teams::Teams(QWidget *parent) : QWidget(parent), ui(new Ui::Teams) {
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
    connect(ui->createTeamButton, &QPushButton::clicked, this, [this]() { createTeam(); });
    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() { cancel(); });
    connect(ui->catCBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Teams::syncComboBox);
    connect(ui->catCBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Teams::checkApplyIsEnabled);
    connect(ui->teamNameForm, SIGNAL(textChanged(const QString &)), this, SLOT(checkApplyIsEnabled()));
}

Teams::~Teams() {
    delete ui;
}

void Teams::setDefault() {
    catTree.updateLists();
    fillComboBox(ui->catCBox, getNames(catTree.categories));
    ui->catCBox->setCurrentIndex(0);
    ui->locCBox->setCurrentIndex(0);
    ui->teamNameForm->clear();
    isCreateTeamActive = false;
    isEditTeamActive = false;
    activeTeam = nullptr;
}

void Teams::init() {
    setDefault();
}

void Teams::fillTable() {
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

        auto editButton = new QPushButton("Edit");
        editButton->setStyleSheet(EditButtonStyle);
        editButton->setCursor(Qt::PointingHandCursor);
        connect(editButton, &QPushButton::clicked, this, [=]{
            setEditingTeam(team);
        });

        auto deleteButton = new QPushButton("Delete");
        deleteButton->setStyleSheet(EditButtonStyle);

        ui->tableWidget->setCellWidget(row, 5, editButton);
        ui->tableWidget->setCellWidget(row, 6, deleteButton);

        ui->tableWidget->setRowHeight(row, ui->tableWidget->rowHeight(row) + 15); // to make padding
    }
}

void Teams::setEditingTeam(ICategory *team) {
    setDefault();
    isEditTeamActive = true;

    activeTeam = team;
    ui->locCBox->setCurrentText(team->location.c_str());
    ui->catCBox->setCurrentText(team->parent->parent->title.c_str());
    ui->subCBox->setCurrentText(team->parent->title.c_str());
    ui->teamNameForm->setText(QString::fromStdString(activeTeam->title));
}


void Teams::fillComboBox(QComboBox *box, std::vector<std::string> items, bool clean) {
    QStringList list;
    if (clean)
        box->clear();
    for (const auto &item: items) {
        list.push_back(QString::fromStdString(item));
    }
    box->addItems(list);
}

void Teams::syncComboBox(int index) {
    if (index >= 0 && (unsigned int)index < catTree.categories.size()){
        ICategory *active = &catTree.categories[index];
        fillComboBox(ui->subCBox, getNames(active->children));
    }
}

std::vector<std::string> Teams::getNames(std::vector<ICategory *> categories) {
    std::vector<std::string> names;
    for (auto cat: categories) {
        names.push_back(cat->title);
    }
    return names;
}

std::vector<std::string> Teams::getNames(std::vector<ICategory> categories) {
    std::vector<std::string> names;
    for (auto cat: categories) {
        names.push_back(cat.title);
    }
    return names;
}

void Teams::applyChanges() {
    std::string location_inbox = ui->locCBox->currentText().toStdString();
    std::string cat_inbox = ui->catCBox->currentText().toStdString();
    std::string sub_inbox = ui->subCBox->currentText().toStdString();
    std::string name_inbox = ui->teamNameForm->text().toStdString();

    if (isCreateTeamActive) {
        ICategory *activeCat = &catTree.categories[ui->catCBox->currentIndex()];
        ICategory *activeSubCategory = &activeCat->children[ui->subCBox->currentIndex()];
        ICategory team = Team(name_inbox, false, activeSubCategory, location_inbox);
        activeSubCategory->children.push_back(team);
        
    } else if (isEditTeamActive){
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
            }

        }
    }
    catTree.updateLists();
    fillTable();
}

void Teams::createTeam() {
    ui->applyButton->setEnabled(false);
    ui->locCBox->setCurrentIndex(0);
    ui->catCBox->setCurrentIndex(0);
    ui->subCBox->setCurrentIndex(0);
    ui->teamNameForm->clear();

    isCreateTeamActive = true;
}

void Teams::checkApplyIsEnabled() {
    bool isEnabled = !ui->teamNameForm->text().isEmpty() && !ui->subCBox->currentText().isEmpty();
    ui->applyButton->setEnabled(isEnabled);
}

void Teams::cancel() {
    isCreateTeamActive = false;
}



