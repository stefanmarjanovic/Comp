#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    Refine *refine;
    AddPlayerDiag *addplayerdiag;
    EditPlayerDiag *editplayerdiag;
};


#endif // MAINWINDOW_H
