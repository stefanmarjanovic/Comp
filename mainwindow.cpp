#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refine.h"
#include "player.h"
#include "team.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"
#include "addteamdialog.h"
#include "database.h"
#include "addcompdiag.h"
#include "payment.h"

//global variables
extern QSqlDatabase tennisTestDB;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set settings to global and use extern
    lastPlayerQuery = "";
    lastVenueQuery = "";
    lastTeamQuery = "";
    lastPaymentQuery = "";
    lastCompQuery = "";
    lastDivisionQuery = "";
    Database::dbOpen();
    loadStyleSheet();
    dbRefresh("ALL");
    ui->playerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playerTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->venueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->venueTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->venueTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->teamTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->teamTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->teamTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->compTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->compTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->compTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->paymentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->paymentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->paymentTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->paymentTable->resizeColumnsToContents();


    connect(ui->playerTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customPlayerMenuRequested(QPoint)));

    connect(ui->venueTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customVenueMenuRequested(QPoint)));

    connect(ui->teamTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customTeamMenuRequested(QPoint)));

    connect(ui->compTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customCompMenuRequested(QPoint)));

    connect(ui->paymentTable, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customTeamMenuRequested(QPoint)));

   ui->paymentEdit->hide();

}
MainWindow::~MainWindow()
{
    Database::dbClose();
    delete ui;
}

void MainWindow::loadStyleSheet()
{
    if(Settings::load()->value("nightmode") == "true")
        this->setStyleSheet("QWidget{background-color: rgb(54, 54, 54); color: rgb(213, 209, 209); } QLineEdit{ background: grey; };");
    else
        this->setStyleSheet("");

}
void MainWindow::dbRefresh(QString tableChoice)
{
    if(tableChoice == "PLAYER" || tableChoice == "ALL")
    {
        ui->playerTable->setModel(Database::modelSearch("PLAYER","ID, first_name as 'First Name', last_name as 'Last Name', dob as 'Date of Birth', Mobile, eMail as 'e-Mail', Type, family_id as 'Family ID', team_id as 'Team ID', case when gender_id = 1 then 'male' when gender_id = 0 then 'female' end as Gender",lastPlayerQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->playerTable->model());
        ui->playerTable->setModel(proxyModel);
        ui->playerTable->setSortingEnabled(true);
        ui->playerTable->sortByColumn(0, Qt::AscendingOrder);
        ui->playerTable->resizeColumnsToContents();
    }

    if(tableChoice == "VENUE" || tableChoice == "ALL")
    {
        ui->venueTable->setModel(Database::modelSearch("VENUE INNER JOIN SUBURB ON VENUE.SUBURB_ID = SUBURB.ID","VENUE.ID as ID,Name,Street_Number as 'Street Number',Street,SUBURB.SUBURB_NAME as Suburb, Postcode, Vacancy_Count as 'Vacant Courts'",lastVenueQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->venueTable->model());
        ui->venueTable->setModel(proxyModel);
        ui->venueTable->setSortingEnabled(true);
        ui->venueTable->sortByColumn(0, Qt::AscendingOrder);
        ui->venueTable->resizeColumnsToContents();

    }

    if(tableChoice == "TEAM" || tableChoice == "ALL")
    {
        ui->teamTable->setModel(Team::search(lastTeamQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->teamTable->model());
        ui->teamTable->setModel(proxyModel);
        ui->teamTable->setSortingEnabled(true);
        ui->teamTable->sortByColumn(0, Qt::AscendingOrder);
        ui->teamTable->resizeColumnsToContents();

    }

    if(tableChoice == "COMP" || tableChoice == "ALL")
    {
        ui->compTable->setModel(Database::search("COMPETITION",lastCompQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->compTable->model());
        ui->compTable->setModel(proxyModel);
        ui->compTable->setSortingEnabled(true);
        ui->compTable->sortByColumn(0, Qt::AscendingOrder);
        ui->compTable->resizeColumnsToContents();

    }

    if(tableChoice == "PAYMENT" || tableChoice == "ALL")
    {
        ui->paymentTable->setModel(Database::search("PAYMENT",""));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->paymentTable->model());
        ui->paymentTable->setModel(proxyModel);
        ui->paymentTable->setSortingEnabled(true);
        ui->paymentTable->sortByColumn(0, Qt::AscendingOrder);
    }
    
       if(tableChoice == "DIVISION" || tableChoice == "ALL")
    {
        ui->teamTable->setModel(Team::search(lastDivisionQuery));
        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(ui->teamTable->model());
        ui->teamTable->setModel(proxyModel);
        ui->teamTable->setSortingEnabled(true);
        ui->teamTable->sortByColumn(0, Qt::AscendingOrder);
        ui->teamTable->resizeColumnsToContents();

    }
  
}

void MainWindow::on_Refine_clicked()
{
    refine = new Refine(this);
    refine->open();

    QObject::connect(refine,SIGNAL(sendWhereQuery(QString)),this,SLOT(getWhereQuery(QString)) );
}

void MainWindow::on_playeAdButton_clicked()
{
    addplayerdiag = new AddPlayerDiag(this);
    addplayerdiag->open();

    QObject::connect(addplayerdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_PlayerEditButton_clicked()
{
    QModelIndexList selection = ui->playerTable->selectionModel()->selectedRows();

    QString id = "";

    if(!selection.isEmpty())
        for(int i = 0; i < ui->playerTable->model()->columnCount(); i++)
        {
            if(ui->playerTable->model()->headerData(i, Qt::Horizontal).toString() == "ID")
            {
                id = ui->playerTable->model()->index(selection.first().row(),i).data().toString();
                break;
            }
        }
    editplayerdiag = new EditPlayerDiag(this);
    editplayerdiag->search(id);
    editplayerdiag->open();

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
    editplayerdiag->open();
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
    editvenuediag->open();
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
    editteamdiag->open();
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

void MainWindow::customCompMenuRequested(QPoint pos)
{
    QModelIndex index=ui->compTable->indexAt(pos);
    QMenu *menu=new QMenu(this);

    menu->addAction("View Schedule",this, std::bind(&MainWindow::on_compViewDraw_clicked,this));
    // menu->addAction("Edit Player",this, std::bind(&MainWindow::getEditPlayerAction,this, playerID));
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

void MainWindow::customPaymentMenuRequested(QPoint pos){
    QModelIndex paymentIndex = ui->paymentTable->indexAt(pos);
    QString paymentID = ui->paymentTable->model()->index(paymentIndex.row(),0).data().toString();
    QMenu *paymentMenu=new QMenu(this);

    //paymentMenu->addAction("Delete Team",this, std::bind(&MainWindow::getDeletePaymentAction,this,paymentID));
    //paymentMenu->addAction("Edit Team",this, std::bind(&MainWindow::getEditPaymentAction,this, paymentID));
    paymentMenu->popup(ui->paymentTable->viewport()->mapToGlobal(pos));
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
    addvenuediag->open();

    QObject::connect(addvenuediag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_venueEdit_clicked()
{
    QModelIndexList selection = ui->venueTable->selectionModel()->selectedRows();

    QString id = "";

    if(!selection.isEmpty())
        for(int i = 0; i < ui->venueTable->model()->columnCount(); i++)
        {
            if(ui->venueTable->model()->headerData(i, Qt::Horizontal).toString() == "ID")
            {
                id = ui->venueTable->model()->index(selection.first().row(),i).data().toString();
                break;
            }
        }

    editvenuediag = new EditVenueDiag(this);

    editvenuediag->search(id);

    editvenuediag->open();

    QObject::connect(editvenuediag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_teamAdd_clicked()
{
    addteamdiag = new addTeamDialog(this);
    addteamdiag->open();

    QObject::connect(addteamdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_teamEdit_clicked()
{
    QModelIndexList selection = ui->teamTable->selectionModel()->selectedRows();

    QString id = "";

    if(!selection.isEmpty())
        for(int i = 0; i < ui->teamTable->model()->columnCount(); i++)
        {
            if(ui->teamTable->model()->headerData(i, Qt::Horizontal).toString() == "id")
            {
                id = ui->teamTable->model()->index(selection.first().row(),i).data().toString();
                break;
            }
        }

    editteamdiag = new EditTeamDiag(this);
    editteamdiag->search(id);
    editteamdiag->open();

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
    settings->open();
    QObject::connect(settings,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
    QObject::connect(settings,SIGNAL(sendLoadStyleSheet()),this,SLOT(loadStyleSheet()) );

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
    QString where = "(first_name LIKE '"+arg1+"%' OR last_name LIKE '"+arg1+"%' OR mobile LIKE '"+arg1+"%' OR email LIKE '"+arg1+"%')";
    lastPlayerQuery = where;
    dbRefresh("PLAYER");
}

void MainWindow::on_quickSearchVenue_textChanged(const QString &arg1)
{
    QString where = "(name LIKE '"+arg1+"%' OR street LIKE '"+arg1+"%')";
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
    dbRefresh("PLAYER");
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
void MainWindow::on_quickSearchComp_textChanged(const QString &arg1)
{
    QString where = "WHERE (COMPETITION.Name LIKE '%"+arg1+"%')";
    lastCompQuery = where;
    dbRefresh("COMP");
}
void MainWindow::on_compEdit_clicked()
{
    QModelIndexList selection = ui->compTable->selectionModel()->selectedRows();
    editcompdiag = new EditCompDiag(this);
    QString id = "";

    if(!selection.isEmpty())
        for(int i = 0; i < ui->compTable->model()->columnCount(); i++)
        {
            if(ui->compTable->model()->headerData(i, Qt::Horizontal).toString() == "id")
            {
                id = ui->compTable->model()->index(selection.first().row(),i).data().toString();
                editcompdiag->search(id);
                break;
            }
        }


    editcompdiag->open();

    QObject::connect(editcompdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_compAdd_clicked()
{
    addcompdiag = new AddCompDiag(this);
    addcompdiag->open();

    QObject::connect(addcompdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_compViewDraw_clicked()
{
    QModelIndexList selection = ui->compTable->selectionModel()->selectedRows();

    QString id = "";
    if(!selection.isEmpty())
    {
        for(int i = 0; i < ui->compTable->model()->columnCount(); i++)
        {
            if(ui->compTable->model()->headerData(i, Qt::Horizontal).toString() == "id")
            {
                id = ui->compTable->model()->index(selection.first().row(),i).data().toString();
                break;
            }
        }
        viewdraw = new ViewDraw(id,this);
        viewdraw->open();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("You must select a competition to continue");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
        {
            break;
        }
        default:
            // should never be reached
            break;
        }
    }
}

void MainWindow::on_paymentAdd_clicked()
{
    addpaymentdiag = new AddPaymentDiag(this);
    addpaymentdiag->open();


    QObject::connect(addpaymentdiag,SIGNAL(sendRefresh(QString)),this,SLOT(dbRefresh(QString)) );
}

void MainWindow::on_compClear_clicked()
{
    lastPlayerQuery = "";
    dbRefresh("COMP");
    ui->quickSearchComp->clear();
}

void MainWindow::on_paymentClear_clicked()
{
    lastPaymentQuery = "";
    dbRefresh("PAYMENT");
    ui->quickSearchPayments->clear();
}

void MainWindow::on_paymentEdit_clicked()
{

}
