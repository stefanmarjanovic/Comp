#ifndef PLAYER_H
#define PLAYER_H

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



using namespace std;

class Player{
        public:
        //player constructor
        Player(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString gender_id,QString FamilyID);

        QString playerID;
        QString firstName;
        QString lastName;
        QString DOB;
        QString mob;
        QString email;
        QString gender_id;
        QString FamilyID;
        static QSqlQueryModel*  search(QString where);  //search players from db
        static QSqlQueryModel*  familySearch(QString where);  //search players from db
        static QString newFamilyID();
};

//prototype declarations
QSqlQueryModel*  dbLoad();  								//import players from db

void addPlayer(Player p);								//add new player to the DB
void deletePlayer(QString id);							//delete existing player
void editPlayer(Player p); 							//edit an exisiting player
Player getPlayer(QString id);
bool verifyPlayer(Player p, bool existingPlayerSearch);

QString toValues(Player p); //NEEDED? return the values for sql e.g. ("bob","saget",etc..)
void mockInsert();



#endif // PLAYER_H
