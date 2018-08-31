#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QTableWidget>

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
void import();  								//import player csv
QTableWidget* viewPlayers(QTableWidget* players);					//print entire player list
bool validEmail(const string& email); 			//regex email validation
void addPlayer(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString type);								//add new player to the DB
void deletePlayer(QString id);							//delete existing player
void editPlayer(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString type); 							//edit an exisiting player
Player getPlayer(QString id);


#endif // PLAYER_H
