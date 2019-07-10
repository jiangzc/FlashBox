#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "gamegrid.h"
extern QNetworkAccessManager *manager;
extern QVector<GameGrid* > grids;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


private:
    Ui::MainWindow *ui;
    int currentPage;
    int totalPage;
    //void turnToPage(int page);
};

#endif // MAINWINDOW_H
