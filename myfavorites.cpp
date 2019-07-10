#include "myfavorite.h"
#include "mainwindow.h"


void MyFavorite::loads(int gameType)
{
    // Read MyFavorites
    this->likesType = gameType;
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
    buff[likesType].append(info);
    for (GameGrid* &g : grids)
        g->refresh();
    if (info.type[0] == likesType)
        return;
    QFile file("./likes.source");
    if (!file.open(QFile::Append))
        return;
    QTextStream out(&file);
    info.type.clear();
    info.type.append(likesType);
    out << info;
    file.close();


    this->grid->AddGame(info);
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
    buff[likesType].removeOne(info);
    for (GameGrid* &g : grids)
        g->refresh();
    // write back to file
    QFile file("./likes.source");
    if (!file.open(QFile::WriteOnly))
        return;
    QTextStream out(&file);
    for (GameInfo &info : buff[likesType])
    {
        if (isLiked(info.name))
        {
            out << info;
        }
    }
    file.close();

}

MyFavorite myFavorite;
