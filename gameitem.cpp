#include "gameitem.h"
#include "ui_gameitem.h"
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QProcess>
#include <QtNetwork>
#include <string>
#include "myfavorite.h"

extern QNetworkAccessManager *manager;
extern void launchGame(QString);
extern MyFavorite myFavorite;
/*
 * Find a memory leak problem when setting StyleSheet of buttons.
 * My solution is using Plain Text in PushButton.
 * If you have better solution, please pull request.
 *
 * > https://forum.qt.io/topic/72195/memory-leak-problem
 * > https://bugreports.qt.io/browse/QTBUG-17151
 * > https://bugreports.qt.io/browse/QTBUG-56492
 * > https://stackoverflow.com/a/55530863
 */

GameItem::GameItem(QWidget *parent, GameInfo info): QWidget(parent), ui(new Ui::GameItem)
{
    ui->setupUi(this);
    this->info = info;
    ui->gameName->setText(info.name);
    ui->pushButton->setIconSize(QSize(100, 30));

    ui->pushButton->setFlat(true);

    //
    ui->likesButton->setIconSize(QSize(30, 30));
    ui->likesButton->setFlat(true);

    ui->progressBar->setVisible(false);
    this->is_downloading = false;
    if (myFavorite.isLiked(info.name))
    {
        ui->likesButton->setIcon(QPixmap("./heart.png"));
        ui->likesButton->setChecked(true);
    }
    else
    {
        ui->likesButton->setIcon(QPixmap("./unheart.png"));
    }
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
        pic_reply = manager->get(QNetworkRequest(QUrl(info.picURL)));
        connect(pic_reply, SIGNAL(finished()), this, SLOT(finished_pic()));
    }
    // swf exist ?
    QFile swf(swf_path);
    if (swf.exists())
    {
        swf_exists = true;
        //ui->pushButton->setText("Open");
        ui->pushButton->setIcon(QPixmap("./open.png"));
    }
    else
    {
        swf_exists = false;
        //ui->pushButton->setText("Download");
        ui->pushButton->setIcon(QPixmap("./download.png"));
    }

}

void GameItem::refresh()
{
    // likes ?
    if (myFavorite.isLiked(info.name))
        ui->likesButton->setChecked(true);
    else
        ui->likesButton->setChecked(false);
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
        //ui->pushButton->setText("Open");
        ui->pushButton->setIcon(QPixmap("./open.png"));
        ui->pushButton->setVisible(true);
        ui->progressBar->setVisible(false);
    }
    else
    {
        swf_exists = false;
        //ui->pushButton->setText("Download");
        ui->pushButton->setIcon(QPixmap("./download.png"));
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
        launchGame(swf_path);
    }
    else
    {
        // download swf
        ui->progressBar->setVisible(true);
        ui->pushButton->setVisible(false);
        this->is_downloading = true;
        swf_reply = manager->get(QNetworkRequest(QUrl(info.swfURL)));
        connect(swf_reply, SIGNAL(finished()), this, SLOT(finished_swf()));
        connect(swf_reply, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(update_progress(qint64, qint64)));

    }
}

void GameItem::finished_pic()
{
    QFile *f = new QFile(pic_path);
    if (!f->open(QIODevice::WriteOnly))
    {
        qDebug() << "finished_pic: cannot open file ";
        return;
    }
    f->write(pic_reply->readAll());
    f->close();
    refresh();
    pic_reply->deleteLater();
    delete f;
    pic_reply = nullptr;
    f = nullptr;
}

void GameItem::finished_swf()
{
    QFile *f = new QFile(swf_path);
    if (!f->open(QIODevice::WriteOnly))
    {
        qDebug() << "finished_swf: cannot open file ";
        return;
    }
    f->write(swf_reply->readAll());
    f->close();
    this->is_downloading = false;
    refresh();
    swf_reply->deleteLater();
    delete f;
    swf_reply = nullptr;
    f = nullptr;
}

void GameItem::update_progress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(int(bytesTotal));
    ui->progressBar->setValue(int(bytesReceived));
}

void GameItem::on_likesButton_clicked(bool checked)
{
    if(checked)
    {
        myFavorite.addLikes(this->info);
        ui->likesButton->setIcon(QPixmap("./heart.png"));
        //myFavorite.removeLikes(this->info);
    }
    else
    {
        myFavorite.removeLikes(this->info);
        ui->likesButton->setIcon(QPixmap("./unheart.png"));
    }
}

void GameItem::refresh_likes()
{
    // likes ?
    if (myFavorite.isLiked(info.name))
    {
        ui->likesButton->setIcon(QPixmap("./heart.png"));
        ui->likesButton->setChecked(true);
    }
    else
    {
        ui->likesButton->setIcon(QPixmap("./unheart.png"));
        ui->likesButton->setChecked(false);
    }
}
