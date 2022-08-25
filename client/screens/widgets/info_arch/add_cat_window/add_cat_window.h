#ifndef QTWORLD_ADD_CAT_DIALOG_H
#define QTWORLD_ADD_CAT_DIALOG_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <click_catch_overlay.h>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class AddCatDialog; }
QT_END_NAMESPACE

class AddCatDialog : public QWidget {
Q_OBJECT

public:
    explicit AddCatDialog(QWidget *parent = nullptr);

    ~AddCatDialog() override;

public slots:
    void onCreateCall(const std::function<void(std::string)> &f);

private:
    ClickCatchOverlay* overlay;
    Ui::AddCatDialog *ui;
};

extern bool isAddButtonClicked;

#endif
