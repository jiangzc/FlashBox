#include "mainwindow.h"
#include <QDir>
#include <QApplication>
#include "gameitem.h"

int main(int argc, char *argv[])
{
    // Set current working dir
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
