#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QWidget>
#include <QDir>
#include <game.h>
#include <QtNetwork>

namespace Ui {
class GameItem;
}

class GameItem : public QWidget
{
    Q_OBJECT

public:
    explicit GameItem(QWidget *parent = nullptr, GameInfo info={}) ;
    ~GameItem();

private slots:
    void on_pushButton_clicked();
    void finished_pic();
    void finished_swf();

private:
    Ui::GameItem *ui;
    GameInfo info;
    bool swf_exists;
    QDir FlashBox_Dir;
    QString pic_path;
    QString swf_path;
    void refresh();
    QNetworkReply *pic_reply;
    QNetworkReply *swf_reply;

};

#endif // GAMEITEM_H
