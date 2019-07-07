#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QWidget>

struct GameInfo {
    int ID;
    QString name;
    QString swfURL;
    QString picURL;
};

namespace Ui {
class GameItem;
}

class GameItem : public QWidget
{
    Q_OBJECT

public:
    explicit GameItem(QWidget *parent = nullptr, GameInfo info={}) ;
    ~GameItem();

private:
    Ui::GameItem *ui;
    GameInfo info;

};

#endif // GAMEITEM_H
