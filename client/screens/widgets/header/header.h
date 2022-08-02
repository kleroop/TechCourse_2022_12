#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QFrame>

#include "../user_profile/user_profile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Header;
}
QT_END_NAMESPACE

class Header : public QWidget
{
    Q_OBJECT

public:
    explicit Header(QWidget *parent = nullptr);
    ~Header() override;
    QFrame *getRightSection();
    UserProfile *UserProfileWidget;

private:
    Ui::Header *ui;
};

#endif // HEADER_H
