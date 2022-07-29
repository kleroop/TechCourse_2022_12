#ifndef QTWORLD_USER_DROPDOWN_H
#define QTWORLD_USER_DROPDOWN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class userDropdown;
}
QT_END_NAMESPACE

class userDropdown : public QWidget
{
    Q_OBJECT

public:
    explicit userDropdown(QWidget *parent = nullptr);
    ~userDropdown() override;

private:
    Ui::userDropdown *ui;
};

#endif
