#ifndef MYFAVORITE_H
#define MYFAVORITE_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "game.h"
#include <QSet>
#include "gamegird.h"

class MyFavorite
{
public:
    //MyFavorite(); // MyFavorite is a special gameType
    int gameType;
    QSet<QString> Items;
    void loads(int gameTypes);
    void addLikes(GameInfo info);
    void removeLikes(GameInfo info);
    bool isLiked(QString info);
    GameGird* gird;
};
extern MyFavorite myFavorite;
#endif // MYFAVORITE_H
