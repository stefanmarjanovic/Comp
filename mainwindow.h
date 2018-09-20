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

#include "refine.h"
#include "addplayerdiag.h"
#include "editplayerdiag.h"
#include "addvenuediag.h"
#include "editvenuediag.h"
#include "addteamdialog.h"
#include "editteamdiag.h"
#include "settings.h"

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
    void getDeleteVenueAction(QString venueID);
    void getEditVenueAction(QString venueID);

    void on_Clear_clicked();

    void on_quickSearch_textChanged(const QString &arg1);

    void on_mockInsert_clicked();

    void on_venueAdd_clicked();

    void on_venueEdit_clicked();

 //   void on_mockInsert_2_clicked();

    void on_teamAdd_clicked();

    void on_teamEdit_clicked();

    void on_actionSetting_triggered();

public slots:
    void customPlayerMenuRequested(QPoint pos);
    void customVenueMenuRequested(QPoint pos);
    void customTeamMenuRequested(QPoint pos);

private:
    Ui::MainWindow *ui;

    QSortFilterProxyModel* proxyModel;
    QSqlQueryModel* search(QString query);

    Refine *refine;
    AddPlayerDiag *addplayerdiag;
    EditPlayerDiag *editplayerdiag;
    AddVenueDiag *addvenuediag;
    EditVenueDiag *editvenuediag;
    addTeamDialog *addteamdiag;
    EditTeamDiag *editteamdiag;
    Settings *settings;

};


#endif // MAINWINDOW_H
