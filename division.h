#ifndef DIVISION_H
#define DIVISION_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QChar>

class division
{
public:
    division();                                 //generic constructor
    division(QString dName);

    QString compId;
    QString divName;

    static void addDivision(division d);                     //add new division
    static division getDivision(QString id);                 //return a division
    static bool verifyName(division d);                      //validate name
    static void editDivsion(int id, QString dName);          //edit division based on ID
    static void deleteDivision(QString id);
};


#endif // DIVISION_H
