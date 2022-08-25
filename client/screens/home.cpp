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

//void Home::switchUserView()
//{
//    HeaderWidget->switchUserView();
//    NavigationWidget->setHideButton();
//    QWidget *mainWidget = NavigationWidget->getMainNavigationWidget();
//    QVector<MainButton *> mainVector = MainNavigationWidget->getMainButtonVector();
//    mainWidget->setFixedHeight(600);
//    if (!mainWidget)
//    {
//        mainWidget = new QWidget;
//        mainWidget->setLayout(new QVBoxLayout);
//    }
//
//    for (auto w:mainVector)
//    {
//        mainWidget->layout()->addWidget(w);
//    }
//}
//
//void Home::switchAdminView()
//{
//    HeaderWidget->switchAdminView();
//    NavigationWidget->setShowButton();
//
//    NavigationWidget->getMainNavigationWidget()->hide();
//
//    ui->localNavigation->addWidget(MainNavigationWidget);
//}

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

// to do
//    if (event->type() == QEvent::MouseButtonPress && watched == userProfile->getSwitchButton())
//    {
//        if (isAdminSwiched)
//        {
//            switchUserView();
//            isAdminSwiched = false;
//        }
//        else
//        {
//            switchAdminView();
//            isAdminSwiched = true;
//        }
//    }

    if (event->type() == QEvent::MouseButtonPress && watched == HeaderWidget->getSaveButton())
    {
        MainNavigationWidget->updateCategories();
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


    // scroll right button action
    if (event->type() == QEvent::MouseButtonPress && watched == HeaderWidget->getRightScrollButton())
    {
        int scrollWidth = HeaderWidget->getScrollArea()->width();
        int x_first = MainNavigationWidget->x() - 11;
        int last = MainNavigationWidget->mainButtonVector.last()->x() + MainNavigationWidget->mainButtonVector.last()->width();
        int scrollAreaWidth = last - scrollWidth + x_first;

        if (scrollAreaWidth >= 70)
        {
            HeaderWidget->getScrollAreaWidget()->scroll(-70,0);
            MainNavigationWidget->scrollPosition = x_first - 70;
        }
        else if (scrollAreaWidth > 0)
        {
            HeaderWidget->getScrollAreaWidget()->scroll(-scrollAreaWidth,0);
            MainNavigationWidget->scrollPosition = x_first - scrollAreaWidth;
        }
    }

    // scroll left button action
    if (event->type() == QEvent::MouseButtonPress && watched == HeaderWidget->getLeftScrollButton())
    {
        int x_first = MainNavigationWidget->x() - 11;

        if (x_first <= -70)
        {
            HeaderWidget->getScrollAreaWidget()->scroll(70,0);
            MainNavigationWidget->scrollPosition = x_first + 70;
        }
        else if (x_first <= 0)
        {
            HeaderWidget->getScrollAreaWidget()->scroll(-x_first,0);
            MainNavigationWidget->scrollPosition = 0;
        }
    }

    int n = MainNavigationWidget->x() - 11;
    if (n != MainNavigationWidget->scrollPosition && clickedActiveButton)
    {
        HeaderWidget->getScrollAreaWidget()->scroll(MainNavigationWidget->scrollPosition,0);
        clickedActiveButton = false;
    }

    return QObject::eventFilter(watched, event);
}
