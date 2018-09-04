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
        Player(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString type);

        QString playerID;
        QString firstName;
        QString lastName;
        QString DOB;
        QString mob;
        QString email;
        QString type;
};

//prototype declarations
QSqlQueryModel*  dbLoad();  								//import players from db
void addPlayer(Player p);								//add new player to the DB
void deletePlayer(QString id);							//delete existing player
void editPlayer(Player p); 							//edit an exisiting player
Player getPlayer(QString id);
bool verifyPlayer(Player p, bool existingPlayerSearch);
void dbOpen();
void dbClose();
QString toValues(Player p); //NEEDED? return the values for sql e.g. ("bob","saget",etc..)




#endif // PLAYER_H
