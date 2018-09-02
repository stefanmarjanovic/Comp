#include <iostream>
#include "player.h"
#include <list>
#include <string>
#include <iomanip>
#include "mainwindow.h" //set width
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QMessageBox>

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
void addPlayer(Player p)								//add new player to the DB
{
    allPlayers.push_back(p);
}
void editPlayer(Player p, QString id)								//add new player to the DB
{
    for(itr = allPlayers.begin(); itr != allPlayers.end(); itr++)
    {
        if((*itr).playerID == id){
            (*itr) = p;
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

bool verifyPlayer(Player p)
{
    QString errorMessage = "";
    QRegExp emailRX(("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
    bool valid = true;

    if(p.firstName.isEmpty())
    {
        valid = false;
        errorMessage += "First Name Invalid.\n";
    }
    else
        for (QChar c : p.firstName)        //string validation
        {
            if(!c.isLetter())
            {
                valid = false;
                errorMessage += "First Name Invalid.\n";
                break;
            }
        }

    if(p.lastName.isEmpty())
    {
        valid = false;
        errorMessage += "Last Name Invalid.\n";
    }
    else
        for (QChar c : p.lastName)        //string validation
        {
            if(!c.isLetter())
            {
                valid = false;
                errorMessage += "Last Name Invalid.\n";
                break;
            }
        }

    if(p.DOB.isEmpty())
    {
        valid = false;
        errorMessage += "DOB Invalid.\n";
    }

    if(p.mob.isEmpty())
    {
        valid = false;
        errorMessage += "Mobile Invalid.\n";
    }
    else
        if(p.mob.length() == 10)
            for (QChar c : p.mob)        //string validation
            {
                if(!c.isNumber())
                {
                    valid = false;
                    errorMessage += "Mobile Invalid Characters.\n";
                    break;
                }
            }
        else
        {
            valid = false;
            errorMessage += "Mobile Invalid Length.\n";
        }

    if(p.email.isEmpty())
    {
        valid = false;
        errorMessage += "Email Invalid.\n";
    }
    else if(!emailRX.exactMatch(p.email))
    {
        valid = false;
        errorMessage += "Email Invalid.\n";
    }


    if(!valid)
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(errorMessage);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    return valid;
}

