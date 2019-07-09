#include <QDir>
#include <QFile>
#include <QTextStream>
#include "game.h"
class MyFavorite
{
public:
    MyFavorite(int gameType);
    int gameType;

};

MyFavorite::MyFavorite(int gameType)
{
    // Read MyFavorites
    this->gameType = gameType;
    QFile file("./likes.source");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    // Read game's content
    while (!in.atEnd())
    {
        GameInfo info;
        in >> info;
        MyFavorites.insert(info.name);
        for (int i = 0; i < info.type.size(); i++)
        {
            buff[info.type[i]].append(info);
        }
    }
    file.close();

}
