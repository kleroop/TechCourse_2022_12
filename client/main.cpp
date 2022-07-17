#include "main_window.h"
#include "QApplication"
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLoggingCategory::setFilterRules("*.debug=true");

    MainWindow w;
    w.show();
    w.setFixedSize(w.size());
    return QApplication::exec();
}
