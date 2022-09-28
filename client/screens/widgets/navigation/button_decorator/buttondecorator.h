#ifndef QTWORLD_BUTTONDECORATOR_H
#define QTWORLD_BUTTONDECORATOR_H

#include <QWidget>
#include "hover/hover.h"
#include <QHoverEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QPushButton>
#include "../../header/header.h"

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
    void hoverEnter();
    void hoverLeave();
    void mouseButtonPress();
    void setDefaultStyleSheet();
    void setData(QWidget *parent, Header *header, QWidget *parentWidget, QString text,
                 QString icon);

    QString text;
    QString icon;
    Hover *hover = nullptr;
    QWidget *parentWidget;
    QWidget *parent;
    Header *header;

private:
    Ui::ButtonDecorator *ui;
};

extern ButtonDecorator *activeButtonDecorator;

#endif // QTWORLD_BUTTONDECORATOR_H
