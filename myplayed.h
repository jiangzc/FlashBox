#ifndef MYPLAYED_H
#define MYPLAYED_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "game.h"
#include <QSet>
#include "gamegrid.h"


class MyPlayed
{
public:
    int playedType; // one of the gamesType
    QSet<QString> Items;
    void loads(int gameTypes);
    void addPlayed(GameInfo info);
    //void removeLikes(GameInfo info);
    bool isPlayed(QString name);
    GameGrid* grid;
};

extern MyPlayed myPlayed;
#endif // MYPLAYED_H
