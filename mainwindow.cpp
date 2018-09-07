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
    dbRefresh();
    ui->playerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playerTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->playerTable, SIGNAL(customContextMenuRequested(QPoint)),
                SLOT(customMenuRequested(QPoint)));
}
MainWindow::~MainWindow()
{
    dbClose();
    delete ui;
}
void MainWindow::dbRefresh()
{
    ui->playerTable->setModel(search(""));
    ui->playerTable->resizeColumnsToContents();
}
void MainWindow::getRefresh()
{
    dbRefresh();
}
void MainWindow::on_Refine_clicked()
{
    refine = new Refine(this);
    refine->show();

    QObject::connect(refine,SIGNAL(sendSearchResult(QSqlQueryModel*)),this,SLOT(getSearchResult(QSqlQueryModel*)) );
}

/*void MainWindow::getLastSearch(QString where)
{

}*/
void MainWindow::on_playeAdButton_clicked()
{
    addplayerdiag = new AddPlayerDiag(this);
    addplayerdiag->show();

    QObject::connect(addplayerdiag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}

void MainWindow::on_PlayerEditButton_clicked()
{
    editplayerdiag = new EditPlayerDiag(this);
    editplayerdiag->show();

    QObject::connect(editplayerdiag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}
void MainWindow::getDeletePlayerAction(QString playerID)
{
    QMessageBox msgBox;
    msgBox.setText("Delete player, are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
    {
        deletePlayer(playerID);
        getRefresh();

        break;
    }
    case QMessageBox::Cancel:
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }
}
void MainWindow::getEditPlayerAction(QString playerID)
{
    editplayerdiag = new EditPlayerDiag(this);
    editplayerdiag->show();
    editplayerdiag->search(playerID);

    QObject::connect(editplayerdiag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}

void MainWindow::getSearchResult(QSqlQueryModel* searchTable)
{

    ui->playerTable->setModel(searchTable);
    ui->playerTable->resizeColumnsToContents();
}
void MainWindow::customMenuRequested(QPoint pos){
    QModelIndex index=ui->playerTable->indexAt(pos);

    QString playerID = ui->playerTable->model()->index(index.row(),0).data().toString();
    QMenu *menu=new QMenu(this);

    menu->addAction("Delete Player",this, std::bind(&MainWindow::getDeletePlayerAction,this,playerID));
    menu->addAction("Edit Player",this, std::bind(&MainWindow::getEditPlayerAction,this, playerID));

    menu->popup(ui->playerTable->viewport()->mapToGlobal(pos));
}
