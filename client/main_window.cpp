#include "main_window.h"
#include "ui_main_window.h"

using json = nlohmann::json;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //todo fix fonts
    ui->errorLabel->setText(""); //todo delete with deleting sample text in ui.errorLabel when fonts fixed
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    double ratio = (double) 642 / (double) 1024;// todo replace hardcoded numbers with picture properties (QPixmap.width)
    int w = ratio * QWidget::size().height();
    ui->loginBgImg->setFixedWidth(w);
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_emailForm_textChanged() {
    QString noErrorFormStyle("font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n"//todo find better solution
                             "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #414C5F;");

    ui->emailForm->setStyleSheet(noErrorFormStyle);
    ui->passwordForm->setStyleSheet(noErrorFormStyle);
    ui->errorLabel->setText("");
}


void MainWindow::on_passwordForm_textChanged() {
    MainWindow::on_emailForm_textChanged();
}


void MainWindow::loginResult(QNetworkReply *reply) {
    json replyJson = toJson(reply);

    QString errorFormStyle("font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n" //todo find better solution
                           "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #D72130;");

    if ((replyJson["status"]) != 200) {
        ui->errorLabel->setText(toQString(replyJson["data"]["message"]));
        ui->emailForm->setStyleSheet(errorFormStyle);
        ui->passwordForm->setStyleSheet(errorFormStyle);
    } else {
        ui->tokenText->setText(toQString(replyJson["data"]["token"]));
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_loginBackButton_clicked() { //todo delete with temporary page(tokenPage)
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_loginButton_clicked()
{
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();
    api.login(adminEmail.toStdString(), adminPassword.toStdString(), [=](const AuthResponse &resp) {
        if (!resp.error.empty()) {
            QMessageBox::information(this, "Connection Error", QString::fromStdString(resp.error));
        } else {
            ui->tokenText->setText(QString::fromStdString(resp.token));
            ui->stackedWidget->setCurrentIndex(1);
        }

    });
}
