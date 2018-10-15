#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMenuBar>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDesktopWidget>

#include "refine.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"
#include "addvenuediag.h"
#include "editvenuediag.h"
#include "addteamdialog.h"
#include "editteamdiag.h"
#include "settings.h"
#include "ui_about.h"
#include "addcompdiag.h"
#include "viewdraw.h"

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
    void dbRefresh(QString tableChoice);
    void getWhereQuery(QString where);

    void getDeletePlayerAction(QString playerID);
    void getEditPlayerAction(QString playerID);
    void getDeleteVenueAction(QString venueID);
    void getEditVenueAction(QString venueID);
    void getDeleteTeamAction(QString TeamID);
    void getEditTeamAction(QString TeamID);

    void on_Clear_clicked();

    void on_quickSearch_textChanged(const QString &arg1);

    void on_mockInsert_clicked();

    void on_venueAdd_clicked();

    void on_venueEdit_clicked();

 //   void on_mockInsert_2_clicked();

    void on_teamAdd_clicked();

    void on_teamEdit_clicked();

    void on_actionSetting_triggered();
    void on_actionAbout_triggered();


    void on_quickSearchVenue_textChanged(const QString &arg1);

    void on_quickSearchTeam_textChanged(const QString &arg1);

    void on_venueClear_clicked();

    void on_teamClear_clicked();

    void on_compEdit_clicked();

    void on_compAdd_clicked();

    void loadStyleSheet();

    void on_compViewDraw_clicked();

public slots:
    void customPlayerMenuRequested(QPoint pos);
    void customVenueMenuRequested(QPoint pos);
    void customTeamMenuRequested(QPoint pos);
    void customCompMenuRequested(QPoint pos);


private:
    Ui::MainWindow *ui;
    QWidget *about;

    QSortFilterProxyModel* proxyModel;
    QSqlQueryModel* search(QString query);

    Refine *refine;
    AddPlayerDiag *addplayerdiag;
    EditPlayerDiag *editplayerdiag;
    AddVenueDiag *addvenuediag;
    EditVenueDiag *editvenuediag;
    addTeamDialog *addteamdiag;
    EditTeamDiag *editteamdiag;
    AddCompDiag *addcompdiag;
    Settings *settings;
    ViewDraw *viewdraw;

    QSettings userSettings;

    QString lastPlayerQuery, lastVenueQuery, lastTeamQuery;
};


#endif // MAINWINDOW_H
