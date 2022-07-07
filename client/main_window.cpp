#include "main_window.h"

static void pushed_s(bool checked)
{
    (void)checked;
    puts("Push");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) // call parent class constructor
{
    counter = 0;

    ui.setupUi(this); // init all ui elements

    ui.label->setText(QString::fromUtf8("Привіт, світ!"));

    timer.setInterval(5000);
    QObject::connect(&timer, &QTimer::timeout, this, &MainWindow::timeout);
    timer.start();

    QObject::connect(ui.pushButton, &QPushButton::clicked, &pushed_s);
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::pushed);
}

void MainWindow::pushed(bool checked)
{
    (void)checked;
    counter++;
    ui.label->setText(QString::fromStdString("pushed " + std::to_string(counter)));
}

void MainWindow::timeout()
{
    this->pushed(false);
}
