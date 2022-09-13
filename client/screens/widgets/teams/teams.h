#ifndef QTWORLD_TEAMS_H
#define QTWORLD_TEAMS_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Teams; }
QT_END_NAMESPACE

class Teams : public QWidget {
Q_OBJECT

public:
    explicit Teams(QWidget *parent = nullptr);

    ~Teams() override;

private:
    Ui::Teams *ui;
};


#endif
