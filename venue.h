#ifndef VENUE_H
#define VENUE_H

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

class Venue{
private:


public:
    Venue(QString venueName, QString streetNumber, QString streetName, QString suburb, QString postcode);	//public constructor
    QString venueName;
    QString streetNumber;
    QString streetName;
    QString suburb;
    QString postcode;

    static QSqlQueryModel*  search(QString where);  								//search players from db
    static Venue getVenue(QString id);
    static QString getSuburb(QString id);
    static void deleteVenue(QString id);
    static void editVenue(Venue v, QString id);
    static bool verifyVenue(Venue v);
    static void addVenue(Venue v);
public slots:

};

//prototype declarations





#endif // VENUE_H
