#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include <QTableWidget>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

class Team
{
public:
    Team(QString name, QString division_id, QString comp_id, QString venue_id);
    QString name, division_id, comp_id, venue_id;

    static QSqlQueryModel*  search(QString where);  								//search players from db
    static Team getTeam(QString id);
    static void deleteTeam(QString id);
    static void editTeam(Team t, QString id);
    static bool verifyTeam(Team t);
    static void addTeam(Team t);
};

#endif // TEAM_H
