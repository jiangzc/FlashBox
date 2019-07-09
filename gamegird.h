#ifndef GAMEGIRD_H
#define GAMEGIRD_H

#include <QWidget>
#include <gameitem.h>
const int ROW = 3;
const int COL = 6;
const int GAME_PER_PAGE = ROW * COL;
namespace Ui {
class GameGird;
}

class GameGird : public QWidget
{
    Q_OBJECT

public:
    explicit GameGird(QWidget *parent, int gameTypeID);
    void keyPressEvent(QKeyEvent *event);
    void AddGame(GameInfo info);
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
    GameItem *GameList[GAME_PER_PAGE];
    QWidget *BlankWidget[GAME_PER_PAGE];

};

#endif // GAMEGIRD_H
