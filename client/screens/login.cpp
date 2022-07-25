#include "login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) : QWidget(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    //TODO: fix fonts
    ui->errorLabel->setText(""); //TODO: delete with deleting sample text in ui.errorLabel when fonts fixed

    connect(ui->emailForm, &QLineEdit::textChanged, this, &Login::onFormTextChanged);
    connect(ui->passwordForm, &QLineEdit::textChanged, this, &Login::onFormTextChanged);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    connect(ui->loginBackButton, &QPushButton::clicked, this, &Login::onLoginBackButtonClicked);
}

Login::~Login()
{
    delete ui;
}

void Login::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    double ratio = (double) 642 / (double) 1024;// TODO: replace hardcoded numbers with picture properties (QPixmap.width)
    int w = ratio * QWidget::size().height();
    ui->loginBgImg->setFixedWidth(w);
}

void Login::onFormTextChanged()
{
    QString noErrorFormStyle("font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n"//todo find better solution
                             "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #414C5F;");

    ui->emailForm->setStyleSheet(noErrorFormStyle);
    ui->passwordForm->setStyleSheet(noErrorFormStyle);
    ui->errorLabel->setText("");
}

void Login::onLoginBackButtonClicked()
{
    //TODO: delete with temporary page(tokenPage)
    ui->stackedWidget->setCurrentIndex(0);
}

void Login::onLoginButtonClicked()
{
    QString adminEmail = ui->emailForm->text();
    QString adminPassword = ui->passwordForm->text();

    QString errorFormStyle("font-family: 'Open Sans';\n""font-style: normal;\n""font-weight: 400;\nfont-size: 14px;\n" //todo find better solution
                           "line-height: 19px;\n""padding-left: 15px;\n""border: 1px solid #D72130;");

    api.login(adminEmail.toStdString(), adminPassword.toStdString(), [=](const AuthResponse &resp) {
        if (!resp.error.empty()) {
            ui->errorLabel->setText(QString::fromStdString(resp.error));
            ui->emailForm->setStyleSheet(errorFormStyle);
            ui->passwordForm->setStyleSheet(errorFormStyle);
        } else {
            ui->tokenText->setText(QString::fromStdString(resp.token));
            ui->stackedWidget->setCurrentIndex(1);
        }
    });
}
