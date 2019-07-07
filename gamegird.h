#ifndef GAMEGIRD_H
#define GAMEGIRD_H

#include <QWidget>
#include <gameitem.h>

namespace Ui {
class GameGird;
}

class GameGird : public QWidget
{
    Q_OBJECT

public:
    explicit GameGird(QWidget *parent, int gameTypeID);
    ~GameGird();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameGird *ui;
    int currentPage;
    int totalPage;
    int gameType;
    void turnToPage(int page);
    GameItem *GameList[12];
    QWidget *BlankWidget[12];
};

#endif // GAMEGIRD_H
