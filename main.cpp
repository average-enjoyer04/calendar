#include "authorization.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Authorization w;
    w.show();
    return a.exec();
}
