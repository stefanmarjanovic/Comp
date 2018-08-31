#include <iostream>
#include "player.h"
#include <list>
#include <string>
#include <iomanip>
#include "mainwindow.h" //set width
#include <QDebug>
#include <QFile>
#include <QStringList>

using namespace std;

//global variables 
list<Player> allPlayers; 
list<Player>::iterator itr; 


Player::Player(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString t){
	playerID = id;			
	firstName = fName; 
	lastName = lName; 
	DOB = dob;
	mob = m;
	email = e; 
	type = t; 
}
void import(){

    QFile file(":/mockData.csv");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
    }
    else
    {
        QTextStream in(&file);
        QStringList player;
        QString line;
        line = in.readLine();
        while(!in.atEnd())
        {
            line = in.readLine();
            player = line.split(",");

            Player newPlayer = Player(player.value(0),player.value(1),player.value(2),player.value(3),player.value(4),player.value(5),player.value(6));
            allPlayers.push_back(newPlayer);
            qDebug() << line;
        }
    }
    file.close();
}

QTableWidget* viewPlayers(QTableWidget *players){
    int rowCount = 0;

    //players->setItem(0,1,*new QTableWidgetItem("test3"));
    for (itr = allPlayers.begin(); itr != allPlayers.end();itr++)
        {
        rowCount++;
        players->setRowCount(rowCount);

        players->setItem(rowCount-1,0,new QTableWidgetItem((*itr).playerID));
        players->setItem(rowCount-1,1,new QTableWidgetItem((*itr).firstName));
        players->setItem(rowCount-1,2,new QTableWidgetItem((*itr).lastName));
        players->setItem(rowCount-1,3,new QTableWidgetItem((*itr).DOB));
        players->setItem(rowCount-1,4,new QTableWidgetItem((*itr).mob ));
        players->setItem(rowCount-1,5,new QTableWidgetItem((*itr).email));



            //cout << (*itr).playerID  +"\t"+ (*itr).firstName +" \t"+ (*itr).lastName +" \t"+ (*itr).DOB +"\t"+ (*itr).mob +"\t"+ (*itr).email << endl;
        }
    return players;
    }
void addPlayer(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString type)								//add new player to the DB
{
    Player newPlayer = Player(id, fName,  lName,  dob,  m,  e,  type);
    allPlayers.push_back(newPlayer);
}
void editPlayer(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString type)								//add new player to the DB
{
    for(itr = allPlayers.begin(); itr != allPlayers.end(); itr++)
    {
        if((*itr).playerID == id){
            (*itr).firstName = fName;
            (*itr).lastName = lName;
            (*itr).DOB = dob;
            (*itr).mob = m;
            (*itr).email = e;
            (*itr).type = type;

            break;
        }
    }
}

Player getPlayer(QString id)
{
    for(itr = allPlayers.begin(); itr != allPlayers.end(); itr++)
    {
        if((*itr).playerID == id){
            break;
        }
    }
    return (*itr);
}

void deletePlayer(QString id){                                // Delete player function
    bool found = false;

    for (itr = allPlayers.begin(); itr != allPlayers.end(); itr++)
    {
        if((*itr).playerID == id)
        {
            itr = allPlayers.erase(itr);
            found = true;
            break;
        }
    }
    if(found == false)
    {
        //TODO add messageboxes
    }
}

