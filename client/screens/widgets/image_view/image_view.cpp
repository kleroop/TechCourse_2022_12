#include <QMimeData>
#include <QFileDialog>
#include <ui_image_view.h>
#include "image_view.h"

QVariant image_view::getImage()
{
    return image;
}
image_view::~image_view()
{
    delete ui;
}
image_view::image_view(QWidget *parent) : QWidget(parent), ui(new Ui::image_view)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}
void image_view::clear()
{
    ui->label->clear();
    image = QVariant::fromValue(nullptr);
}
void image_view::mousePressEvent(QMouseEvent *event)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), nullptr,
                                                    tr("Image Files (*.png *.jpg)"));
    QImage img;
    if (!img.load(fileName)) {
        event->ignore();
        return;
    }
    setImage(img);
    event->accept();
}
void image_view::setImage(QImage img)
{
    image = QVariant::fromValue(img.scaled(128, 128));
    ui->label->setPixmap(QPixmap::fromImage(qvariant_cast<QImage>(image)));
}

void image_view::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
void image_view::dropEvent(QDropEvent *event)
{
    const QMimeData *mime = event->mimeData();
    // check for our needed mime type, here a file or a list of files
    if (mime->hasUrls()) {
        QStringList pathList;
        QList<QUrl> urlList = mime->urls();
        QImage img;


        if (img.load(urlList.at(0).toLocalFile())) {
            setImage(img);
            event->accept();
            return ;
        }
    }
    event->ignore();
}
void image_view::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}
void image_view::dragLeaveEvent(QDragLeaveEvent *event)
{
    QWidget::dragLeaveEvent(event);
}
