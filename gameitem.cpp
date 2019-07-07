#include "gameitem.h"
#include "ui_gameitem.h"

GameItem::GameItem(QWidget *parent, GameInfo info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->info = info;
    ui->gameName->setText(info.name);

}

GameItem::~GameItem()
{
    delete ui;
}
