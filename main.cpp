#include "blmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BLMainWindow w;
    w.show();

    return a.exec();
}
