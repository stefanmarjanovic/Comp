#ifndef COMPETITION_H
#define COMPETITION_H


#include <QWidget>
#include <Qstring>
#include <QVector>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

class Competition
{
public:
    Competition();
   ~Competition();
    Competition(QString sDate, int numOfTeams, QString name);

    int id; 				//	Comp id
    int division; 			//	link to the division id
    int boxes; 				//	num of boxes in the comp
    int rounds; 			// 	number of rounds in the comp
    int teams; 				// number of teams in the comp


    QString name;			// 	Comp name
    QString startDate; 		//
    QString finishDate;		//	Important dates
    QString year; 			//


    int *teamIds;                   		//dynamic array to team references
    QVector<QVector<int> > draw;			//Two dimensional array for storing rounds


    void addMatch(int r, int c, int val);
    static void printSchedule();
    static void addNewComp();
    static void editComp();
    static void deleteComp();
    int getTeamById(int i);
};

#endif // COMPETITION_H
