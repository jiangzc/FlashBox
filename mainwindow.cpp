#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameitem.h"
#include "gamegrid.h"
#include <QWidget>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QtDebug>
#include <cmath>
#include "myfavorite.h"


extern void ReadSourceFile();
QNetworkAccessManager *manager;
QVector<GameGrid* > grids;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSourceFile();
    manager = new QNetworkAccessManager(this);

    for (int i = 0; i < gamesType.size(); i++)
    {
        GameGrid *g  = new GameGrid(ui->tabWidget, i);
        ui->tabWidget->addTab(g, gamesType[i]);
        grids.append(g);
    }
    ui->tabWidget->currentWidget()->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

