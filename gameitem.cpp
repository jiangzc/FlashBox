#include "gameitem.h"
#include "ui_gameitem.h"
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QProcess>

GameItem::GameItem(QWidget *parent, GameInfo info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->info = info;
    ui->gameName->setText(info.name);
    ui->progressBar->setVisible(false);
    FlashBox_Dir = QDir::home();
    FlashBox_Dir.cd("FlashBox");
    // picture exist ?
    QFile pic(FlashBox_Dir.filePath(QString::number(info.ID) + ".jpg"));
    if (pic.exists())
    {
        ui->pictureBox->setScaledContents(true);
        ui->pictureBox->setPixmap(QPixmap(FlashBox_Dir.filePath(QString::number(info.ID) + ".jpg")));
    }
    // swf exist ?
    QFile swf(FlashBox_Dir.filePath(QString::number(info.ID) + ".swf"));
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


}

GameItem::~GameItem()
{
    delete ui;
}

void GameItem::on_pushButton_clicked()
{
    if (swf_exists)
    {
        ui->pushButton->setText("a");
        QProcess *proc = new QProcess();
        QStringList args;
        args.append( FlashBox_Dir.filePath(QString::number(info.ID) + ".swf"));
        proc->start("./flashplayer", args);
        //proc->waitForFinished();
    }
}
