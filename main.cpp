#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"
//----------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QDesktopWidget* dsk = QApplication::desktop();
    if(dsk->height() >= 600)
        w.setMinimumHeight(300);
    if(dsk->width() >= 900)
        w.setMinimumWidth(600);

    w.show();

    return a.exec();
}
