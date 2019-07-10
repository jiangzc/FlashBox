#ifndef MYFAVORITE_H
#define MYFAVORITE_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "game.h"
#include <QSet>
#include "gamegrid.h"

class MyFavorite
{
public:
    int likesType; // one of the gamesType
    QSet<QString> Items;
    void loads(int gameTypes);
    void addLikes(GameInfo info);
    void removeLikes(GameInfo info);
    bool isLiked(QString name);
    GameGrid* grid;

};
extern MyFavorite myFavorite;
#endif // MYFAVORITE_H
