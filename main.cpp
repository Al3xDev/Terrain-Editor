/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
