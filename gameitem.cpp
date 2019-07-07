#include "gameitem.h"
#include "ui_gameitem.h"

GameItem::GameItem(QWidget *parent, QString info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    //if (info.ID != 0) BUG!!!
    {
        ui->gameName->setText(info);
        //this->gameID = info.ID;
        //this->swfURL = info.swfURL;
        //this->picURL = info.picURL;
    }

}

GameItem::~GameItem()
{
    delete ui;
}
