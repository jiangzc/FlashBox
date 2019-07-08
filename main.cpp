#include "mainwindow.h"
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QDesktopWidget>
#include <QtDebug>
#include "gameitem.h"

extern void checkFiles();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Set current working dir to where the exe file exist
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    // check files
    checkFiles();
    // move to center
    MainWindow w;
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    w.show();

    return a.exec();
}
