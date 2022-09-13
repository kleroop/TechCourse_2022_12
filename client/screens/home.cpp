#include "home.h"
#include "ui_Home.h"
#include "info_arch.h"
#include "teams.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home)
{
    ui->setupUi(this);

    this->HeaderWidget = new Header(this);
    auto prof = new UserProfile(this->HeaderWidget);
    this->userProfile = prof;
    this->HeaderWidget->getRightSection()->addWidget(prof);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);

    this->NavigationWidget = new Navigation(this, HeaderWidget);
    ui->localNavigation->replaceWidget(ui->navigationMock, NavigationWidget);
    delete ui->navigationMock;

    auto InfoArchWidget = new InfoArch(this);
    ui->stackedWidget->addWidget(InfoArchWidget);

    auto TeamsWidget = new Teams(this);
    ui->stackedWidget->addWidget(TeamsWidget);
    ui->stackedWidget->setCurrentIndex(3);

    this->MainNavigationWidget = new MainNavigation(HeaderWidget, HeaderWidget);
    HeaderWidget->getMainNavigationLayout()->addWidget(this->MainNavigationWidget);

    qApp->installEventFilter(this);

    isAdminSwiched = true;
}

Home::~Home()
{
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void Home::switchUserView()
{
    HeaderWidget->switchUserView();
    NavigationWidget->setHideButton();
    QWidget *mainWidget = NavigationWidget->getMainNavigationWidget();
    QVector<MainButton *> mainVector = MainNavigationWidget->getMainButtonVector();
    if (!mainWidget)
    {
        mainWidget = new QWidget;
        mainWidget->setLayout(new QVBoxLayout);
    }

    for (auto w:mainVector)
    {
        mainWidget->layout()->addWidget(w);
    }
}

void Home::switchAdminView()
{
    HeaderWidget->switchAdminView();
    NavigationWidget->setShowButton();

    NavigationWidget->getMainNavigationWidget()->hide();

    ui->localNavigation->addWidget(MainNavigationWidget);
}

bool Home::event(QEvent *event)
{
    if (activeButtonDecorator && previousActiveButtonDecorator == nullptr)
    {
        if (activeMainButton)
        {
            activeMainButton->setDefaultStyleSheet();
            activeMainButton = nullptr;
            previousActiveMainButton = nullptr;
        }
        previousActiveButtonDecorator = activeButtonDecorator;
    }
    else if (activeMainButton && previousActiveMainButton == nullptr)
    {
        if (activeButtonDecorator) {
            activeButtonDecorator->setDefaultStyleSheet();
            activeButtonDecorator = nullptr;
            previousActiveButtonDecorator = nullptr;
        }
        previousActiveMainButton = activeMainButton;
    }
    return QWidget::event(event);
}

bool Home::eventFilter(QObject *watched, QEvent *event)
{

    if (event->type() == QEvent::MouseButtonPress && watched == userProfile->getSwitchButton())
    {
        if (isAdminSwiched)
        {
            switchUserView();
            isAdminSwiched = false;
        }
        else
        {
            switchAdminView();
            isAdminSwiched = true;
        }
    }

    return QObject::eventFilter(watched, event);
}
