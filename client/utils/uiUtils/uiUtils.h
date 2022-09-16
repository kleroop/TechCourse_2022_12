#ifndef QTWORLD_UIUTILS_H
#define QTWORLD_UIUTILS_H

#include <QWidget>
#include <QLayoutItem>
#include <QLayout>

static std::vector<QWidget *> getLayoutWidgets(QLayout *container) {
    QLayoutItem *item;
    std::vector<QWidget *> result;
    for (int i = 0; i < container->count(); i++) {
        item = container->itemAt(i);
        result.push_back(item->widget());
    }
    return result;
}

static void clearLayout(QLayout *container) {
    QLayoutItem *item;
    while ((item = container->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

#endif
