#include "game.h"
#include <QTextStream>

GameInfo::GameInfo()
{
    ;
}

GameInfo::~GameInfo()
{
    ;
}


QTextStream &operator<<(QTextStream &output, GameInfo &info)
{
    output << info.toString();
    return output;
}

QTextStream &operator>>(QTextStream &input, GameInfo &info)
{
    QString line = input.readLine().mid(6);
    QTextStream linesStream(&line);
    linesStream >> info.name;
    int t;
    while (!linesStream.atEnd())
    {
        linesStream >> t;
        info.type.append(t);
    }
    info.picURL = input.readLine();
    info.swfURL = input.readLine();
    return input;
}

QString GameInfo::toString()
{
    QString s("[Game] " + name);
    for (int &i : type)
        s += QString::number(i);
    s += '\n';
    s += picURL + '\n';
    s += swfURL + '\n';
    return s;
}
