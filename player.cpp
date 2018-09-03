#include "player.h"
#include "mainwindow.h" //set width


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
QSqlQueryModel* dbLoad(){

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlDatabase tennisTestDB = QSqlDatabase::addDatabase("QMYSQL");
    tennisTestDB.setHostName("127.0.0.1");
    tennisTestDB.setDatabaseName("tennisTestDB");
    tennisTestDB.setUserName("root");

    if(tennisTestDB.isValid())
    {
        tennisTestDB.open();
        if(tennisTestDB.isOpen())
        {
            qDebug() << "opened successfully";

            QSqlQuery search(tennisTestDB);

            search.prepare("SELECT * FROM players");
            search.exec();

            if(search.isActive())
            {
                model->setQuery(search);
                tennisTestDB.close();
            }
            else
                qDebug() << " Query not active: " << search.lastError() << endl;
        }
        else
            qDebug() << "DB not open";
    }
    else
        qDebug() << "DB not valid";

    return model;
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

