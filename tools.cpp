#include <QFile>
#include <QVector>
#include <QTextStream>
#include "game.h"

QVector<QVector<GameInfo>> buff;
QStringList gamesType;

void ReadSourceFile(QString path) // relative path
{
    // Read source.txt
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    // Read games' type
    QString firstline = in.readLine();
    gamesType = firstline.split(" ");
    for (int i = 0; i < gamesType.size(); i++)
        buff.append(QVector<GameInfo>());
    // Read game's content
    while (!in.atEnd())
    {
        GameInfo info;
        QString line = in.readLine().mid(6);
        QTextStream linesStream(&line);
        linesStream >> info.name >> info.ID >> info.type;
        info.picURL = in.readLine();
        info.swfURL = in.readLine();
        buff[info.type].append(info);
    }
}
