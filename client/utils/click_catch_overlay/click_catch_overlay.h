#ifndef QTWORLD_CLICK_CATCH_OVERLAY_H
#define QTWORLD_CLICK_CATCH_OVERLAY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ClickCatchOverlay; }
QT_END_NAMESPACE

class ClickCatchOverlay : public QWidget {
Q_OBJECT

public:
    explicit ClickCatchOverlay(QWidget *parent, bool blurred = false);

    ~ClickCatchOverlay() override;

signals:
    void clicked();

private:
    Ui::ClickCatchOverlay *ui;

    void resizeEvent(QResizeEvent *event);
};


#endif
