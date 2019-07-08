#include "gameitem.h"
#include "ui_gameitem.h"
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QProcess>
//#include <QColorGroup>

// Find a memory leak problem when setting StyleSheet of button:
// please refer to urls below
// https://forum.qt.io/topic/72195/memory-leak-problem
// https://bugreports.qt.io/browse/QTBUG-17151
// https://bugreports.qt.io/browse/QTBUG-56492

GameItem::GameItem(QWidget *parent, GameInfo info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->info = info;
    ui->gameName->setText(info.name);
    ui->progressBar->setVisible(false);
    // set path
    FlashBox_Dir = QDir::home();
    FlashBox_Dir.cd("FlashBox");
    pic_path = FlashBox_Dir.filePath("cached/" + info.name + ".jpg");
    swf_path = FlashBox_Dir.filePath("games/" + info.name + ".swf");
    // picture exist ?
    QFile pic(pic_path);
    if (pic.exists())
    {
        ui->pictureBox->setScaledContents(true);
        ui->pictureBox->setPixmap(QPixmap(pic_path));
    }
    else
    {
        // download picture
    }
    // swf exist ?
    QFile swf(swf_path);
    if (swf.exists())
    {
        swf_exists = true;
        ui->pushButton->setText("Open");
        //ui->pushButton->setStyleSheet("background-color: rgb(0, 120, 0);color: rgb(255, 255, 255);");

    }
    else
    {
        swf_exists = false;
        ui->pushButton->setText("Download");
        //ui->pushButton->setStyleSheet("background-color: rgb(71, 142, 213);;color: rgb(255, 255, 255);");
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
        ui->pushButton->setText("Open");
        //ui->pushButton->setStyleSheet("background-color: rgb(0, 120, 0);color: rgb(255, 255, 255);");
    }
    else
    {
        swf_exists = false;
        ui->pushButton->setText("Download");
        //ui->pushButton->setStyleSheet("background-color: rgb(71, 142, 213);;color: rgb(255, 255, 255);");
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
