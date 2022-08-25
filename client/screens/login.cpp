#include "login.h"
#include "ui_Login.h"

int resizeImgWidth(const std::string &path, QLabel *label) {
    QPixmap picture = QPixmap(QString::fromStdString(path));
    double width = picture.width();
    double height = picture.height();
    double ratio = width / height;
    int w = ratio * label->height();

    return w;
}

Login::Login(QWidget *parent) : QWidget(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    ui->errorLabel->setText("");

    connect(ui->emailForm, &QLineEdit::textChanged, this, &Login::onFormTextChanged);
    connect(ui->passwordForm, &QLineEdit::textChanged, this, &Login::onFormTextChanged);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    connect(ui->loginBackButton, &QPushButton::clicked, this, &Login::onLoginBackButtonClicked);

    ui->loginBgImg->setFixedWidth(resizeImgWidth("://Resources/image_BG.png", ui->loginBgImg));//todo make it work
}

Login::~Login() {
    delete ui;
}

void Login::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    ui->loginBgImg->setFixedWidth(resizeImgWidth("://Resources/image_BG.png", ui->loginBgImg));
}

void Login::onFormTextChanged() {
    QString noErrorFormStyle(
            "font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n"//todo find better solution
            "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #414C5F;");

    ui->emailForm->setStyleSheet(noErrorFormStyle);
    ui->passwordForm->setStyleSheet(noErrorFormStyle);
    ui->errorLabel->setText("");
}

void Login::onLoginBackButtonClicked() {
    //TODO: delete with temporary page(tokenPage)
    ui->stackedWidget->setCurrentIndex(0);
}

void Login::onLoginButtonClicked() {
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();

    QString errorFormStyle(
            "font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n" //todo find better solution
            "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #D72130;");

    api.login(adminEmail.toStdString(), adminPassword.toStdString(), [=](const AuthResponse &resp) {
        if (!resp.error.empty()) {
            ui->errorLabel->setText(QString::fromStdString(resp.error));
            ui->emailForm->setStyleSheet(errorFormStyle);
            ui->passwordForm->setStyleSheet(errorFormStyle);
        } else {
            ui->tokenText->setText(QString::fromStdString(resp.token));
            onLoginSuccess();
            //ui->stackedWidget->setCurrentIndex(1);
        }
    });
}
