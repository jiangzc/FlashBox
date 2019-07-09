#include <QWidget>
#include <QVector>
#include <QTextStream>
#ifndef GAME_H
#define GAME_H

struct GameInfo {
    QVector<int> type;
    QString name;
    QString swfURL;
    QString picURL;
    GameInfo();
    ~GameInfo();
    QString toString();
    bool operator==(const GameInfo &info);
    friend QTextStream &operator<<(QTextStream &output, GameInfo &info);
    friend QTextStream &operator>>(QTextStream &input, GameInfo &info);
};
extern QStringList gamesType;
extern QVector<QVector<GameInfo>> buff; // buff[GameTypeId][GameId]
#endif // GAME_H
