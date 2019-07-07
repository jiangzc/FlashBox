#include <QFile>
#include <QVector>
#include <QTextStream>
#include "gameitem.h"

extern QVector<GameInfo> buff;

void ReadSourceFile(QString path) // relative path
{
    // Read source.txt
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        GameInfo info;
        info.ID = in.readLine().mid(6).toInt();
        info.name = in.readLine();
        info.swfURL = in.readLine();
        buff.append(info);
    }
}
