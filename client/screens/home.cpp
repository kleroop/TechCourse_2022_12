#include "home.h"
#include "ui_Home.h"


Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home)
{

    ui->setupUi(this);

    this->HeaderWidget = new Header(this);
    auto prof = new UserProfile(this->HeaderWidget);
    this->HeaderWidget->getRightSection()->addWidget(prof);
    delete ui->headerPlaceholder;
    ui->headerFrame->layout()->addWidget(HeaderWidget);

    this->NavigationWidget = new Navigation(this, HeaderWidget);
    ui->localNavigation->replaceWidget(ui->navigationMock, NavigationWidget);
    delete ui->navigationMock;

    this->MainNavigationWidget = new MainNavigation(HeaderWidget, HeaderWidget);
    HeaderWidget->getMainNavigationLayout()->addWidget(this->MainNavigationWidget);

    qApp->installEventFilter(prof);

}

Home::~Home()
{
    delete ui;
}

void Home::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

bool Home::event(QEvent * e)
{
    if ((activeButtonDecorator != nullptr) && (previousActiveButtonDecorator == nullptr))
    {
        if (activeMainButton)
        {
            activeMainButton->setDefaultStyleSheet();
            activeMainButton = nullptr;
            previousActiveMainButton = nullptr;
        }
        previousActiveButtonDecorator = activeButtonDecorator;
    }
    else if ((activeMainButton != nullptr) && (previousActiveMainButton == nullptr))
    {
        if (activeButtonDecorator)
        {
            activeButtonDecorator->setDefaultStyleSheet();
            activeButtonDecorator = nullptr;
            previousActiveButtonDecorator = nullptr;
        }
        previousActiveMainButton = activeMainButton;
    }
    return QWidget::event(e);
}