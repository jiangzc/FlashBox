#include "myplayed.h"
#include "mainwindow.h"

void MyPlayed::loads(int gameType)
{
    // Read MyFavorites
    this->playedType = gameType;
    QFile file("./played.source");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    // Read game's content
    while (!in.atEnd())
    {
        GameInfo info;
        in >> info;
        Items.insert(info.name);
        buff[playedType].append(info);
    }
    file.close();

}

bool MyPlayed::isPlayed(QString name)
{
    if (Items.find(name) == Items.end())
        return false;
    return true;
}

void MyPlayed::addPlayed(GameInfo info)
{
    Items.insert(info.name);
    buff[playedType].append(info);
    if (info.type[0] == playedType)
        return;
    QFile file("./played.source");
    if (!file.open(QFile::Append))
        return;
    QTextStream out(&file);
    info.type.clear();
    info.type.append(playedType);
    out << info;
    file.close();
    this->grid->AddGame(info);
}

MyPlayed myPlayed;
