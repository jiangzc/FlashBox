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


extern void ReadSourceFile(QString path);
QNetworkAccessManager *manager;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSourceFile("./source.txt");
    manager = new QNetworkAccessManager(this);

    for (int i = 0; i < gamesType.size(); i++)
    {
        QWidget *widget = new QWidget(this);
        GameGird *g  = new GameGird(widget, i);
        ui->tabWidget->addTab(widget, gamesType[i]);
    }
    ui->tabWidget->currentWidget()->setFocus();
    //GameGird *g1  = new GameGird(ui->tab_3, 1);


}

MainWindow::~MainWindow()
{
    delete ui;
}

