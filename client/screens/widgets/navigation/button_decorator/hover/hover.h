#ifndef QTWORLD_HOVER_H
#define QTWORLD_HOVER_H

#include <QWidget>
#include "QPushButton"

QT_BEGIN_NAMESPACE
namespace Ui {
class Hover;
}
QT_END_NAMESPACE

class Hover : public QWidget
{
    Q_OBJECT

public:
    explicit Hover(QWidget *parent = nullptr, QPushButton *hoverButton = nullptr,
                   QWidget *ParentButton = nullptr, const QString &text = nullptr);
    ~Hover() override;

    void setHoverText();
    void setPos();

private:
    Ui::Hover *ui;
    QPushButton *hoverButton;
    QWidget *ParentWidget;
    QString text;
};

#endif // QTWORLD_HOVER_H
