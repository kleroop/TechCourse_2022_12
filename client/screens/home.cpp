#include "home.h"
#include "ui_Home.h"
#include "info_arch.h"

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

    this->MainNavigationWidget = new MainNavigation(HeaderWidget, HeaderWidget, true);
    auto *layout = new QHBoxLayout;
    HeaderWidget->getScrollAreaWidget()->setLayout(layout);
    layout->addWidget(this->MainNavigationWidget);

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
    ui->stackedWidget->setCurrentIndex(0);
    isAdminSwiched = false;
    previousActiveMainButton = nullptr;
    activeMainButton = nullptr;
    delete this->MainNavigationWidget;
    this->MainNavigationWidget = new MainNavigation(NavigationWidget, HeaderWidget, false);
    NavigationWidget->getMainNavigationWidget()->layout()->addWidget(MainNavigationWidget);
    HeaderWidget->switchUserView();
    NavigationWidget->setHideButton();
}

void Home::switchAdminView()
{
    ui->stackedWidget->setCurrentIndex(2);
    activeMainButton = nullptr;
    previousActiveMainButton = nullptr;
    delete this->MainNavigationWidget;
    this->MainNavigationWidget = new MainNavigation(HeaderWidget, HeaderWidget, true);
    HeaderWidget->switchAdminView();
    NavigationWidget->setShowButton();
    HeaderWidget->getScrollAreaWidget()->layout()->addWidget(MainNavigationWidget);
    isAdminSwiched = true;
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
        if (activeButtonDecorator)
        {
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
        }
        else
        {
            switchAdminView();
        }
    }

    if (event->type() == QEvent::MouseButtonPress && watched == HeaderWidget->getSaveButton())
    {
        MainNavigationWidget->updateCategoriesAdminView();
        activeMainButton = nullptr;
    }

    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[0]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[1]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[2]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[3]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[4]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[5]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[6]) ui->stackedWidget->setCurrentIndex(2);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[7]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[8]) ui->stackedWidget->setCurrentIndex(0);
    if (event->type() == QEvent::MouseButtonPress && watched == NavigationWidget->buttonDecoratorArray[9]) ui->stackedWidget->setCurrentIndex(0);

    if (isAdminSwiched ){
        // scroll right button action
        if (event->type() == QEvent::MouseButtonPress
            && watched == HeaderWidget->getRightScrollButton()) {
            int scrollWidth = HeaderWidget->getScrollArea()->width();
            int x_first = MainNavigationWidget->x() - 11;
            int last = MainNavigationWidget->mainButtonVector.last()->x()
                    + MainNavigationWidget->mainButtonVector.last()->width();
            int scrollAreaWidth = last - scrollWidth + x_first;

            if (scrollAreaWidth >= 70) {
                HeaderWidget->getScrollAreaWidget()->scroll(-70, 0);
                MainNavigationWidget->scrollPosition = x_first - 70;
            } else if (scrollAreaWidth > 0) {
                HeaderWidget->getScrollAreaWidget()->scroll(-scrollAreaWidth, 0);
                MainNavigationWidget->scrollPosition = x_first - scrollAreaWidth;
            }
        }

        // scroll left button action
        if (event->type() == QEvent::MouseButtonPress
            && watched == HeaderWidget->getLeftScrollButton()) {
            int x_first = MainNavigationWidget->x() - 11;

            if (x_first <= -70) {
                HeaderWidget->getScrollAreaWidget()->scroll(70, 0);
                MainNavigationWidget->scrollPosition = x_first + 70;
            } else if (x_first <= 0) {
                HeaderWidget->getScrollAreaWidget()->scroll(-x_first, 0);
                MainNavigationWidget->scrollPosition = 0;
            }
        }

        int n = MainNavigationWidget->x() - 11;
        if (n != MainNavigationWidget->scrollPosition && clickedActiveButton) {
            HeaderWidget->getScrollAreaWidget()->scroll(MainNavigationWidget->scrollPosition, 0);
            clickedActiveButton = false;
        }
    }
    return QObject::eventFilter(watched, event);
}