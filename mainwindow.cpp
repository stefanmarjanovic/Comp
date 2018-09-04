#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refine.h"
#include "player.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbOpen();
    ui->playerTable->setModel(dbLoad());
    getPlayer("-1");
   // ui->playerTable = viewPlayers(ui->playerTable);
}
MainWindow::~MainWindow()
{
    dbClose();
    delete ui;
}

void MainWindow::on_Refine_clicked()
{
    //ui->playerTable = viewPlayers(ui->playerTable);

    //refine = new Refine(this);
    //refine->show();
}

void MainWindow::on_playeAdButton_clicked()
{
    addplayerdiag = new AddPlayerDiag(this);
    addplayerdiag->show();

}

void MainWindow::on_PlayerEditButton_clicked()
{
    editplayerdiag = new EditPlayerDiag(this);
    editplayerdiag->show();
}
