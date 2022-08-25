#ifndef QTWORLD_MAIN_BUTTON_H
#define QTWORLD_MAIN_BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include "../../header/header.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainButton;
}
QT_END_NAMESPACE

class MainButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MainButton(QWidget *parent = nullptr, Header *header = nullptr, const QString& text = nullptr);
    ~MainButton() override;

    bool event(QEvent *) override;
    void mouseButtonPress(QHoverEvent * event);
    void setDefaultStyleSheet();
    void setActiveStyleSheet();

private:
    Ui::MainButton *ui;
    QString text;
    Header* header;
};

extern MainButton * activeMainButton;

#endif // QTWORLD_MAIN_BUTTON_H
