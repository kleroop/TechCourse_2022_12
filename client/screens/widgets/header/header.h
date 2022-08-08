#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class Header;
}
QT_END_NAMESPACE

class Header : public QWidget
{
    Q_OBJECT

public:
    explicit Header(QWidget *parent = nullptr, std::vector<QWidget *> right_widgets = {});
    ~Header() override;
    QHBoxLayout *getRightSection();

private:
    Ui::Header *ui;
};

#endif // HEADER_H
