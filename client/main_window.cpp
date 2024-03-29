#include "main_window.h"
#include <ui_main_window.h>
#include "QApplication"
#include "QRect"
#include "QScreen"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Adding our screens here
    ui->stackedWidget->addWidget(&login);
    ui->stackedWidget->addWidget(&home);

    ui->stackedWidget->setCurrentIndex(0);

    connect(&login, &Login::onLoginSuccess, this, &MainWindow::onLoginSuccess);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginSuccess()
{
    ui->stackedWidget->setCurrentIndex(1);
}
