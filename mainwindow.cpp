#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refine.h"
#include "player.h"
#include "team.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"
#include "addteamdialog.h"
#include "database.h"

//global variables
extern QSqlDatabase tennisTestDB;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lastPlayerQuery = "";
    lastVenueQuery = "";
    lastTeamQuery = "";
    Database::dbOpen();
    dbRefresh("ALL");
    ui->playerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playerTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->playerTable->resizeColumnsToContents();

    ui->venueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->venueTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->venueTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->venueTable->resizeColumnsToContents();

    ui->teamTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->teamTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->teamTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->teamTable->resizeColumnsToContents();


    connect(ui->playerTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customPlayerMenuRequested(QPoint)));

    connect(ui->venueTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customVenueMenuRequested(QPoint)));

    connect(ui->teamTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customTeamMenuRequested(QPoint)));

}
MainWindow::~MainWindow()
{
    Database::dbClose();
    delete ui;
}

void MainWindow::dbRefresh(QString tableChoice)
{
    if(tableChoice == "PLAYER" || tableChoice == "ALL")
    {
        ui->playerTable->setModel(Player::search(lastPlayerQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->playerTable->model());
        ui->playerTable->setModel(proxyModel);
        ui->playerTable->setSortingEnabled(true);
        ui->playerTable->sortByColumn(0, Qt::AscendingOrder);
    }

    if(tableChoice == "VENUE" || tableChoice == "ALL")
    {
        ui->venueTable->setModel(Venue::search(lastVenueQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->venueTable->model());
        ui->venueTable->setModel(proxyModel);
        ui->venueTable->setSortingEnabled(true);
        ui->venueTable->sortByColumn(0, Qt::AscendingOrder);
    }

    if(tableChoice == "TEAM" || tableChoice == "ALL")
    {
        ui->teamTable->setModel(Team::search(lastTeamQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->teamTable->model());
        ui->teamTable->setModel(proxyModel);
        ui->teamTable->setSortingEnabled(true);
        ui->teamTable->sortByColumn(0, Qt::AscendingOrder);
    }
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

    QObject::connect(addplayerdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_PlayerEditButton_clicked()
{
    editplayerdiag = new EditPlayerDiag(this);
    editplayerdiag->show();

    QObject::connect(editplayerdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
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
        dbRefresh("PLAYER");

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

    QObject::connect(editplayerdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
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
        dbRefresh("VENUE");

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

    QObject::connect(editvenuediag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::getDeleteTeamAction(QString teamID)
{
    QMessageBox msgBox;
    msgBox.setText("Delete Team");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
    {
        Team::deleteTeam(teamID);
        dbRefresh("TEAM");

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
void MainWindow::getEditTeamAction(QString teamID)
{
    editteamdiag = new EditTeamDiag(this);
    editteamdiag->show();
    editteamdiag->search(teamID);

    QObject::connect(editteamdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::getWhereQuery(QString where)
{
    lastPlayerQuery = where;
    dbRefresh("PLAYER");
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

void MainWindow::customTeamMenuRequested(QPoint pos)
{
    QModelIndex teamIndex = ui->teamTable->indexAt(pos);
    QString teamID = ui->teamTable->model()->index(teamIndex.row(),0).data().toString();
    QMenu *teamMenu=new QMenu(this);

    teamMenu->addAction("Delete Team",this, std::bind(&MainWindow::getDeleteTeamAction,this,teamID));
    teamMenu->addAction("Edit Team",this, std::bind(&MainWindow::getEditTeamAction,this, teamID));
    teamMenu->popup(ui->teamTable->viewport()->mapToGlobal(pos));
}


void MainWindow::on_mockInsert_clicked()
{
    mockInsert();
    lastPlayerQuery = "";
    dbRefresh("ALL");
}

void MainWindow::on_venueAdd_clicked()
{
    addvenuediag = new AddVenueDiag(this);
    addvenuediag->show();

    QObject::connect(addvenuediag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_venueEdit_clicked()
{
    editvenuediag = new EditVenueDiag(this);
    editvenuediag->show();

    QObject::connect(editvenuediag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_teamAdd_clicked()
{
    addteamdiag = new addTeamDialog(this);
    addteamdiag->show();

    QObject::connect(addteamdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_teamEdit_clicked()
{
    editteamdiag = new EditTeamDiag(this);
    editteamdiag->show();

    QObject::connect(editteamdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}
QSqlQueryModel* MainWindow::search(QString query)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare(query);
    search.exec();

    if(search.isActive())
    {
        model->setQuery(search);
        qDebug() << " Query active: " << search.executedQuery();

    }
    else
        qDebug() << " Query not active: " << search.executedQuery();

    return model;
}

void MainWindow::on_actionSetting_triggered()
{
    settings = new Settings(this);
    settings->show();
    QObject::connect(settings,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );

}

void MainWindow::on_actionAbout_triggered()
{
    about = new QWidget();
    Ui::About aboutInstance;
    aboutInstance.setupUi(about);
    aboutInstance.version->setText("Vesion: " + QString(VERSION_STRING));

    QPropertyAnimation *anim = new QPropertyAnimation();
    anim->setTargetObject(about);
    anim->setPropertyName("windowOpacity");

    anim->setDuration(1000);
    anim->setStartValue(0);
    anim->setEndValue(1);
    //anim->setEasingCurve(QEasingCurve::InBack);
    anim->start(QPropertyAnimation::DeleteWhenStopped);

    about->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    about->setGeometry( QStyle::alignedRect(
                            Qt::LeftToRight,
                            Qt::AlignCenter,
                            about->size(),
                            qApp->desktop()->availableGeometry()
                        ));
    about->show();
}

void MainWindow::on_quickSearch_textChanged(const QString &arg1)
{
    QString where = "WHERE (first_name LIKE '"+arg1+"%' OR last_name LIKE '"+arg1+"%' OR mobile LIKE '"+arg1+"%' OR email LIKE '"+arg1+"%')";
    lastPlayerQuery = where;
    dbRefresh("PLAYER");
}

void MainWindow::on_quickSearchVenue_textChanged(const QString &arg1)
{
    QString where = "WHERE (name LIKE '"+arg1+"%' OR street LIKE '"+arg1+"%')";
    lastVenueQuery = where;
    dbRefresh("VENUE");
}

void MainWindow::on_quickSearchTeam_textChanged(const QString &arg1)
{
    QString where = " WHERE (t.name LIKE '%"+arg1+"%')";
    lastTeamQuery = where;
    dbRefresh("TEAM");
}

void MainWindow::on_Clear_clicked()
{
    lastPlayerQuery = "";
    dbRefresh("TEAM");
    ui->quickSearch->clear();
}

void MainWindow::on_venueClear_clicked()
{
    lastVenueQuery = "";
    dbRefresh("VENUE");
    ui->quickSearchVenue->clear();
}

void MainWindow::on_teamClear_clicked()
{
    lastTeamQuery = "";
    dbRefresh("TEAM");
    ui->quickSearchTeam->clear();
}
