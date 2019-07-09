#include <QWidget>
#include <QVector>
#ifndef GAME_H
#define GAME_H

struct GameInfo {
    QVector<int> type;
    QString name;
    QString swfURL;
    QString picURL;
};
extern QStringList gamesType;
extern QVector<QVector<GameInfo>> buff; // buff[GameTypeId][GameId]


#endif // GAME_H
