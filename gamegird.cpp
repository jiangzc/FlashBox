#include "gamegird.h"
#include "ui_gamegird.h"
#include "gameitem.h"
#include <QWidget>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QtDebug>
#include <cmath>
#include <QKeyEvent>
#include <QTabWidget>
#include <QMessageBox>


extern QVector<QVector<GameInfo>> buff;



GameGird::GameGird(QWidget *parent, int gameTypeID) :
    QWidget(parent),
    ui(new Ui::GameGird)
{
    ui->setupUi(this);
    this->gameType = gameTypeID;
    this->setFocusPolicy(Qt::StrongFocus);
    currentPage = 1;
    totalPage = int(ceil(1.0 * buff[gameType].size() / GAME_PER_PAGE));
    ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));

    for (int i = 0; i < GAME_PER_PAGE; i++)
    {
        GameList[i] = nullptr;
        BlankWidget[i] = new QWidget(this);
    }
    turnToPage(1);
}

GameGird::~GameGird()
{
    delete ui;
}

void GameGird::on_pushButton_clicked()
{
    turnToPage(currentPage - 1);
}

void GameGird::on_pushButton_2_clicked()
{
    turnToPage(currentPage + 1);
}

void GameGird::turnToPage(int page)
{
    if (totalPage == 0)
    {
        for (int i = 0; i < GAME_PER_PAGE; i++)
        {
            ui->gridLayout->addWidget(BlankWidget[i], i / COL, i % COL);
        }
    }
    if (page > totalPage || page < 1)
    {
        qDebug() << "turnToPage: out of range";
        return;
    }
    for (GameItem* item : GameList)
    {
        if (item != nullptr && item->is_downloading)
        {
            QMessageBox::warning(item, "Warning", "Cannot page while downloading");
            return;
        }
    }
    currentPage = page;
    ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));
    // release memeory
    for (int i = 0; i < GAME_PER_PAGE; i++)
    {
        ui->gridLayout->removeWidget(GameList[i]);
        ui->gridLayout->removeWidget(BlankWidget[i]);
        delete GameList[i];
        GameList[i] = nullptr;
    }

    // list is full of games
    if (page < totalPage)
    {
        for (int i = 0; i < GAME_PER_PAGE; i++)
        {
            GameItem *item = new GameItem(this, buff[gameType][(page-1) * GAME_PER_PAGE + i]);
            GameList[i] = item;
            ui->gridLayout->addWidget(item, i / COL, i % COL);
        }
        return;
    }
    // list maybe have blank
    if (page == totalPage)
    {
        int gameLeft = buff[gameType].size() - (totalPage - 1) * GAME_PER_PAGE;
        for (int i = 0; i < gameLeft; i++)
        {
            GameItem *item = new GameItem(this, buff[gameType][(page-1) * GAME_PER_PAGE + i]);
            GameList[i] = item;
            ui->gridLayout->addWidget(item, i / COL, i % COL);
        }
        // fill blank with empty widget
        for (int i = gameLeft; i < GAME_PER_PAGE; i++)
        {
            ui->gridLayout->addWidget(BlankWidget[i], i / COL, i % COL);
        }
    }
}

void GameGird::keyPressEvent( QKeyEvent * event )
{
    QTabWidget *w = dynamic_cast<QTabWidget*>(this->parent()->parent());
    switch (event->key())
    {
        case Qt::Key_Up:
            turnToPage(currentPage - 1);
            break;
        case Qt::Key_Down:
            turnToPage(currentPage + 1);
            break;
        case Qt::Key_Left:
            w->setCurrentIndex(w->currentIndex() - 1);
            break;
        case Qt::Key_Right:
             w->setCurrentIndex(w->currentIndex() + 1);
            break;
        default:
            break;
    }

}

void GameGird::AddGame(GameInfo info)
{
    totalPage = int(ceil(1.0 * buff[gameType].size() / GAME_PER_PAGE));
    ui->label->setText(QString::number(currentPage) + "/" + QString::number(totalPage));
    for (int i = 0; i < GAME_PER_PAGE; i++)
    {
        if (GameList[i] == nullptr)
        {
            GameList[i] = new GameItem(this, info);
            ui->gridLayout->addWidget(GameList[i], i / COL, i % COL);
            return;
        }
   }
}

