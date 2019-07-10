#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameitem.h"
#include "gamegird.h"
#include <QWidget>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QtDebug>
#include <cmath>
#include "myfavorite.h"


extern void ReadSourceFile();
QNetworkAccessManager *manager;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSourceFile();
    manager = new QNetworkAccessManager(this);

    for (int i = 0; i < gamesType.size(); i++)
    {
        GameGird *g  = new GameGird(ui->tabWidget, i);
        ui->tabWidget->addTab(g, gamesType[i]);
        myFavorite.girds.append(g);
        if (i == 10)
            myFavorite.gird = g;
    }
    ui->tabWidget->currentWidget()->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

