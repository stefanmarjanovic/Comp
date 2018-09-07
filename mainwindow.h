#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMenu>
#include "refine.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Refine_clicked();
    void on_playeAdButton_clicked();
    void on_PlayerEditButton_clicked();
    void dbRefresh();
    void getRefresh();
    void getWhereQuery(QString where);
    void getDeletePlayerAction(QString playerID);
    void getEditPlayerAction(QString playerID);

    void on_Clear_clicked();

public slots:
    void customMenuRequested(QPoint pos);

private:
    Ui::MainWindow *ui;
    Refine *refine;
    AddPlayerDiag *addplayerdiag;
    EditPlayerDiag *editplayerdiag;
};


#endif // MAINWINDOW_H
