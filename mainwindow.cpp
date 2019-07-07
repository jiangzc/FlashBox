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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSourceFile("./source.txt");
    GameGird *g1  = new GameGird(ui->tab_3, 1);
    g1->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

