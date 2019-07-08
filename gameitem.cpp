#include "gameitem.h"
#include "ui_gameitem.h"
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QProcess>
#include <QtNetwork>

/*
 * Find a memory leak problem when setting StyleSheet of buttons:
 * Please refer to the urls below
 * > https://forum.qt.io/topic/72195/memory-leak-problem
 * > https://bugreports.qt.io/browse/QTBUG-17151
 * > https://bugreports.qt.io/browse/QTBUG-56492
 *
 * My solution is using QIcon(QPixmap("path")).
 * > https://stackoverflow.com/a/55530863
 * If you have better solution, please pull request.
 */

GameItem::GameItem(QWidget *parent, GameInfo info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->info = info;
    ui->gameName->setText(info.name);
    ui->pushButton->setIconSize(QSize(100, 30));
    ui->progressBar->setVisible(false);
    // set path
    FlashBox_Dir = QDir::home();
    FlashBox_Dir.cd("FlashBox");
    pic_path = FlashBox_Dir.filePath("cached/" + info.name + ".jpg");
    swf_path = FlashBox_Dir.filePath("games/" + info.name + ".swf");
    // picture exist ?
    QFile pic(pic_path);
    ui->pictureBox->setScaledContents(true);
    if (pic.exists())
    {
        ui->pictureBox->setPixmap(QPixmap(pic_path));
    }
    else
    {
        ui->pictureBox->setPixmap(QPixmap("./loading.jpeg"));
        // download picture
    }
    // swf exist ?
    QFile swf(swf_path);
    if (swf.exists())
    {
        swf_exists = true;
        ui->pushButton->setText("Open");
    }
    else
    {
        swf_exists = false;
        ui->pushButton->setText("Download");
    }
    // swf downloading ?
    if (QFile::exists(FlashBox_Dir.filePath("cached/" + info.name + ".download")))
    {
        ui->pushButton->setText("Loading");
        ui->pushButton->setEnabled(false);
    }



}

void GameItem::refresh()
{
    // picture exist ?
    QFile pic(pic_path);
    if (pic.exists())
    {
        ui->pictureBox->setScaledContents(true);
        ui->pictureBox->setPixmap(QPixmap(pic_path));
    }
    // swf exist ?
    QFile swf(swf_path);
    if (swf.exists())
    {
        swf_exists = true;
        ui->pushButton->setIcon(QIcon(QPixmap("./open.png")));
    }
    else
    {
        swf_exists = false;
        ui->pushButton->setIcon(QIcon(QPixmap("./download.png")));
    }
}
GameItem::~GameItem()
{
    delete ui;
}

void GameItem::on_pushButton_clicked()
{
    if (swf_exists)
    {
        QProcess *proc = new QProcess();
        QStringList args;
        args.append(swf_path);
        proc->start("./flashplayer", args);
        //proc->waitForFinished();
    }
    else
    {
        // download swf
    }
}
