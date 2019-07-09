#include <QFile>
#include <QDir>
#include <QVector>
#include <QTextStream>
#include <QtDebug>
#include <QProcess>
#include "game.h"

QVector<QVector<GameInfo>> buff;
QStringList gamesType;

void ReadSourceFile(QDir dir)
{
    // Read main.source
    QFile file(dir.filePath("main.source"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    // Read the first line (games' type)
    QString firstline = in.readLine();
    gamesType = firstline.split(" ");
    for (int i = 0; i < gamesType.size(); i++)
        buff.append(QVector<GameInfo>());
    // Read game's content
    while (!in.atEnd())
    {
        GameInfo info;
        in >> info;
        for (int i = 0; i < info.type.size(); i++)
        {
            buff[info.type[i]].append(info);
        }
    }
    file.close();
    //
    // Read other source
    QStringList filter;
    filter << "*.source";
    for (QString fileName: dir.entryList(filter))
    {
        if (fileName == "main.source")
            continue;
        QFile file(dir.filePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);

        // Read game's content
        while (!in.atEnd())
        {
            GameInfo info;
            in >> info;
            for (int i = 0; i < info.type.size(); i++)
            {
                buff[info.type[i]].append(info);
            }
        }
        file.close();
    }
}

void checkFiles()
{
    if (!QFile::exists("./flashplayer"))
        qDebug() << "Not Found: flashplayer";
    if (!QFile::exists("./main.source"))
        qDebug() << "Not Found: ./main.source";
    // FlashBox Dir exist ?
    QDir dir(QDir::home());
    if (!dir.exists("FlashBox"))
    {
        bool ok = dir.mkdir("FlashBox");
        if(!ok)
            qDebug() << "Cannot create FlashBox dir";
    }
    if (!dir.exists("FlashBox/cached"))
    {
        bool ok = dir.mkdir("FlashBox/cached");
        if(!ok)
            qDebug() << "Cannot create cached dir";
    }
    if (!dir.exists("FlashBox/games"))
    {
        bool ok = dir.mkdir("FlashBox/games");
        if(!ok)
            qDebug() << "Cannot create games dir";
    }
}

void launchGame(QString swf_path)
{
    QProcess *proc = new QProcess();
    QStringList args;
    args.append(swf_path);
    proc->start("./flashplayer", args);
    qDebug() << "launching game";
    // wait for flashplayer
    std::string cmd = "sleep 0.5 && ";
    // focus on flashplayer
    cmd += "xdotool windowactivate `xdotool search --onlyvisible --pid " + std::to_string(proc->processId())+ "` &&";
    // maximize flashplayer
    cmd += "xdotool key --window `xdotool search --onlyvisible --pid " +std::to_string(proc->processId())+ "` ctrl+3 ctrl+f";
    qDebug() << cmd.c_str();
    system(cmd.c_str());
}
