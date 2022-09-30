#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImage>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui {
class image_view;
}
QT_END_NAMESPACE

class image_view : public QWidget
{
    Q_OBJECT
public slots:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    QVariant image;
    Ui::image_view *ui;
public:
    void setImage(QImage img);
    image_view(QWidget *parent);
    ~image_view() override;
    QVariant getImage();
    void clear();
};

#endif // IMAGE_VIEW_H
