#include "mainwindow.h"
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include <QtDebug>
#include "gameitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Set current working dir to where the exe file exist
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    // FlashBox Dir exist ?
    QDir dir(QDir::home());
    if (!dir.exists("FlashBox"))
    {
        bool ok = dir.mkdir("FlashBox");
        if(!ok)
            qDebug() << "Cannot create dir";
    }

    // move to center
    MainWindow w;
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    w.show();

    return a.exec();
}
