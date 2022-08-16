#ifndef QTWORLD_ADD_CAT_DIALOG_H
#define QTWORLD_ADD_CAT_DIALOG_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

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
    Ui::AddCatDialog *ui;
    std::string* namePtr;
};


#endif
