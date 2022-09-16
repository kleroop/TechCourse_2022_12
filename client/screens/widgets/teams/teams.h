#ifndef QTWORLD_TEAMS_H
#define QTWORLD_TEAMS_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"
#include "QComboBox"
#include "QHBoxLayout"

#include "api.h"
#include "models/categories_model.h"
#include "uiUtils.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Teams; }
QT_END_NAMESPACE

class Teams : public QWidget {
Q_OBJECT

public:
    explicit Teams(QWidget *parent = nullptr);

    ~Teams() override;

private:
    Api api;
    CategoriesTree catTree;
    ICategory* activeTeam = nullptr;

    void fillTable();
    void fillComboBox(QComboBox *box, std::vector<std::string> items, bool clean = true);

    void init();

    std::vector<std::string> getNames(std::vector<ICategory*> categories);
    std::vector<std::string> getNames(std::vector<ICategory> categories);

    void setEditingTeam(ICategory *team);

    void applyChanges();

    Ui::Teams *ui;


};


#endif
