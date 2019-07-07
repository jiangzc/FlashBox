#include <QWidget>
#ifndef GAME_H
#define GAME_H

struct GameInfo {
    int type;
    int ID;
    QString name;
    QString swfURL;
    QString picURL;
};
extern QStringList gamesType;
extern QVector<QVector<GameInfo>> buff; // buff[GameTypeId][GameId]


#endif // GAME_H
