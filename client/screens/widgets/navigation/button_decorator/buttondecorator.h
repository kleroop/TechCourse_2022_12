#ifndef QTWORLD_BUTTONDECORATOR_H
#define QTWORLD_BUTTONDECORATOR_H

#include <QWidget>
#include "hover/hover.h"
#include <QHoverEvent>
#include <QEvent>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class ButtonDecorator;
}
QT_END_NAMESPACE

class ButtonDecorator : public QPushButton
{
    Q_OBJECT

public:
    explicit ButtonDecorator(QWidget *parent = nullptr);
    ~ButtonDecorator() override;

    bool event(QEvent *) override;
    void hoverEnter(QHoverEvent * event);
    void hoverLeave(QHoverEvent * event);
    void mouseButtonPress(QHoverEvent * event);

    void setDefaultStyleSheet();
    void setData(QWidget *parent, QWidget *parentWidget, QString text, QString icon);

    QString text;
    QString icon;
    Hover* hover = nullptr;
    QWidget *parentWidget;
    QWidget *parent;
private:
    Ui::ButtonDecorator *ui;
};

#endif // QTWORLD_BUTTONDECORATOR_H
