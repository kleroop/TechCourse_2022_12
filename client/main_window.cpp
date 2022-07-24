#include "main_window.h"
#include <ui_main_window.h>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->addWidget(&login);

    ui->stackedWidget->setCurrentIndex(0);
}


MainWindow::~MainWindow() {
    delete ui;
}
