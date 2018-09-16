#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refine.h"
#include "player.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"
#include "addteamdialog.h"

//global variables
QString lastQuery;
QSqlDatabase tennisTestDB = QSqlDatabase::addDatabase("QMYSQL");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lastQuery = "";
    dbOpen();
    dbRefresh();
    ui->playerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playerTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->playerTable->resizeColumnsToContents();

    ui->venueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->venueTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->venueTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->venueTable->resizeColumnsToContents();


    connect(ui->playerTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customPlayerMenuRequested(QPoint)));

    connect(ui->venueTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customVenueMenuRequested(QPoint)));
}
MainWindow::~MainWindow()
{
    dbClose();
    delete ui;
}
void MainWindow::dbOpen()
{
    tennisTestDB.setHostName("127.0.0.1");
    tennisTestDB.setDatabaseName("tennisTestDB");
    tennisTestDB.setUserName("root");
    if(tennisTestDB.isValid())
    {
        tennisTestDB.open();
        if(!tennisTestDB.isOpen())
            qDebug() << "DB not open";
    }
    else
        qDebug() << "DB not valid";

}
void MainWindow::dbClose()
{
    tennisTestDB.close();
}
void MainWindow::dbRefresh()
{
    ui->playerTable->setModel(Player::search(lastQuery));
    ui->venueTable->setModel(Venue::search(""));

    proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->playerTable->model());
    ui->playerTable->setModel(proxyModel);
    ui->playerTable->setSortingEnabled(true);
    ui->playerTable->sortByColumn(0, Qt::AscendingOrder);

    proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->venueTable->model());
    ui->venueTable->setModel(proxyModel);
    ui->venueTable->setSortingEnabled(true);
    ui->venueTable->sortByColumn(0, Qt::AscendingOrder);
}
void MainWindow::getRefresh()
{
    dbRefresh();
}
void MainWindow::on_Refine_clicked()
{
    refine = new Refine(this);
    refine->show();

    QObject::connect(refine,SIGNAL(sendWhereQuery(QString)),this,SLOT(getWhereQuery(QString)) );
}

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
    msgBox.setText("Delete Player");
    msgBox.setInformativeText("Are you sure?");
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
void MainWindow::getDeleteVenueAction(QString venueID)
{
    QMessageBox msgBox;
    msgBox.setText("Delete Venue");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
    {
        Venue::deleteVenue(venueID);
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
void MainWindow::getEditVenueAction(QString venueID)
{
    editvenuediag = new EditVenueDiag(this);
    editvenuediag->show();
    editvenuediag->search(venueID);

    QObject::connect(editvenuediag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}

void MainWindow::getWhereQuery(QString where)
{
    lastQuery = where;
    dbRefresh();
}
void MainWindow::customPlayerMenuRequested(QPoint pos)
{
    QModelIndex index=ui->playerTable->indexAt(pos);
    QString playerID = ui->playerTable->model()->index(index.row(),0).data().toString();
    QMenu *menu=new QMenu(this);

    menu->addAction("Delete Player",this, std::bind(&MainWindow::getDeletePlayerAction,this,playerID));
    menu->addAction("Edit Player",this, std::bind(&MainWindow::getEditPlayerAction,this, playerID));
    menu->popup(ui->playerTable->viewport()->mapToGlobal(pos));
}
void MainWindow::customVenueMenuRequested(QPoint pos)
{
    QModelIndex venueIndex=ui->venueTable->indexAt(pos);
    QString venueID = ui->venueTable->model()->index(venueIndex.row(),0).data().toString();
    QMenu *venueMenu=new QMenu(this);

    venueMenu->addAction("Delete Venue",this, std::bind(&MainWindow::getDeleteVenueAction,this,venueID));
    venueMenu->addAction("Edit Venue",this, std::bind(&MainWindow::getEditVenueAction,this, venueID));
    venueMenu->popup(ui->venueTable->viewport()->mapToGlobal(pos));
}
void MainWindow::on_Clear_clicked()
{
    lastQuery = "";
    ui->quickSearch->clear();
}

void MainWindow::on_quickSearch_textChanged(const QString &arg1)
{
    QString where = "WHERE (first_name LIKE '"+arg1+"%' OR last_name LIKE '"+arg1+"%' OR mobile LIKE '"+arg1+"%' OR email LIKE '"+arg1+"%')";
    lastQuery = where;
    dbRefresh();
}

void MainWindow::on_mockInsert_clicked()
{
    mockInsert();
    lastQuery = "";
    dbRefresh();
}

void MainWindow::on_venueAdd_clicked()
{
    addvenuediag = new AddVenueDiag(this);
    addvenuediag->show();

    QObject::connect(addvenuediag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}

void MainWindow::on_venueEdit_clicked()
{
    editvenuediag = new EditVenueDiag(this);
    editvenuediag->show();

    QObject::connect(editvenuediag,SIGNAL(sendRefresh()),this,SLOT(getRefresh()) );
}

void MainWindow::on_teamAdd_clicked()
{
    addteamdiag = new addTeamDialog(this);
    addteamdiag->show();
}

void MainWindow::on_teamEdit_clicked()
{
    editteamdiag = new EditTeamDiag(this);
    editteamdiag->show();
}
