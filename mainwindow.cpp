#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameitem.h"
#include <QWidget>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QtDebug>
#include <cmath>

const int GAME_PER_PAGE = 5;
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
        GameList[i] = nullptr;
        BlankWidget[i] = new QWidget();
    }
    turnToPage(1);
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
        turnToPage(currentPage);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (currentPage < totalPage)
    {
        currentPage++;
        ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));
        turnToPage(currentPage);
    }
}

void MainWindow::turnToPage(int page)
{
    if (page > totalPage)
    {
        qDebug() << "turnToPage: out of range";
        return;
    }
    // release memeory
    for (int i = 0; i < GAME_PER_PAGE; i++)
    {
        ui->verticalLayout->removeWidget(GameList[i]);
        ui->verticalLayout->removeWidget(BlankWidget[i]);
        delete GameList[i];
        GameList[i] = nullptr;
    }

    // list is full of games
    if (page < totalPage)
    {
        for (int i = 0; i < GAME_PER_PAGE; i++)
        {
            GameItem *item = new GameItem(this, buff[(page-1) * GAME_PER_PAGE + i]);
            GameList[i] = item;
            ui->verticalLayout->addWidget(item);
        }
        return;
    }
    // list maybe have blank
    if (page == totalPage)
    {
        int gameLeft = buff.size() - (totalPage - 1) * GAME_PER_PAGE;
        for (int i = 0; i < gameLeft; i++)
        {
            GameItem *item = new GameItem(this, buff[(page-1) * GAME_PER_PAGE + i]);
            GameList[i] = item;
            ui->verticalLayout->addWidget(item);
        }
        // fill blank with empty widget
        for (int i = 0; i < GAME_PER_PAGE - gameLeft; i++)
        {
            ui->verticalLayout->addWidget(BlankWidget[i]);
        }
    }
}
