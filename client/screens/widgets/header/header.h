#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QScrollArea>

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
    QWidget *getScrollAreaWidget();
    QScrollArea *getScrollArea();
    QPushButton *getSaveButton();
    QPushButton *getRightScrollButton();
    QPushButton *getLeftScrollButton();
    QFrame *getCategories();

    void setSectionName(const QString &text);
    void switchUserView();
    void switchAdminView();

private:
    Ui::Header *ui;
};

#endif // HEADER_H
