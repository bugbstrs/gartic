#include "mainwindow.h"
#include <Qt6/QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    //w.show();
    return a.exec();
}