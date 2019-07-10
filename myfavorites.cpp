#include "myfavorite.h"


void MyFavorite::loads(int gameType)
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
        Items.insert(info.name);
        buff[gameType].append(info);
    }
    file.close();

}

void MyFavorite::addLikes(GameInfo info)
{
    Items.insert(info.name);
    buff[gameType].append(info);
    for (GameGird* &g : girds)
        g->refresh();
    if (info.type[0] == 10)
        return;
    QFile file("./likes.source");
    if (!file.open(QFile::Append))
        return;
    QTextStream out(&file);
    info.type.clear();
    info.type.append(10);
    out << info;
    file.close();


    this->gird->AddGame(info);
}

bool MyFavorite::isLiked(QString name)
{
    if (Items.find(name) == Items.end())
        return false;
    return true;
}

void MyFavorite::removeLikes(GameInfo info)
{
    Items.remove(info.name);
    buff[gameType].removeOne(info);
    for (GameGird* &g : girds)
        g->refresh();
    // write back to file
    QFile file("./likes.source");
    if (!file.open(QFile::WriteOnly))
        return;
    QTextStream out(&file);
    for (GameInfo &info : buff[gameType])
    {
        if (isLiked(info.name))
        {
            out << info;
        }
    }
    file.close();

}

MyFavorite myFavorite;
