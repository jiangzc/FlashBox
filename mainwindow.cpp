#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameitem.h"
#include <QWidget>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <cmath>

const int GAME_PER_PAGE = 7;
static GameItem *GameList[GAME_PER_PAGE];
static QWidget *BlankWidget[GAME_PER_PAGE];
extern QVector<GameInfo> buff;
QVector<GameInfo> buff;

extern void ReadSourceFile(QString path);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSourceFile("./source.txt");
    currentPage = 1;
    totalPage = int(ceil(1.0 * buff.size() / GAME_PER_PAGE));
    ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));

    for (int i = 0; i < GAME_PER_PAGE; i++)
    {
        BlankWidget[i] = new QWidget();
    }
    for (int i = 0; i < GAME_PER_PAGE ; i++)
    {
        GameItem *item = new GameItem(this, buff[i].name);
        GameList[i] = item;
        ui->verticalLayout->addWidget(item);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (currentPage > 1)
    {
        currentPage--;
        ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (currentPage < totalPage)
    {
        currentPage++;
        ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));
    }
}
