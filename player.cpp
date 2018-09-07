#include "player.h"
#include "mainwindow.h" //set width


//global variables 
QSqlDatabase tennisTestDB = QSqlDatabase::addDatabase("QMYSQL");

Player::Player(QString id, QString fName, QString lName, QString dob, QString m, QString e, QString t){
    playerID = id;
    firstName = fName;
    lastName = lName;
    DOB = dob;
    mob = m;
    email = e;
    gender_id = t;
}

void dbOpen()
{
    tennisTestDB.setHostName("127.0.0.1");
    tennisTestDB.setDatabaseName("tennisTestDB");
    tennisTestDB.setUserName("root");
    if(tennisTestDB.isValid())
    {
        tennisTestDB.open();
        if(!tennisTestDB.isOpen())
            qDebug() << "DB not open";
    }
    else
        qDebug() << "DB not valid";

}
void dbClose()
{
    tennisTestDB.close();
}


QSqlQueryModel* dbLoad()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare("SELECT * FROM players");
    search.exec();

    if(search.isActive())
    {
        model->setQuery(search);
    }
    else
        qDebug() << " Query not active: " << search.lastError() << endl;


    return model;
}
QSqlQueryModel* search(QString where)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare("SELECT * FROM players " + where);
    search.exec();

    if(search.isActive())
    {
        model->setQuery(search);
        qDebug() << " Query active: " << search.executedQuery();

    }
    else
        qDebug() << " Query not active: " << search.executedQuery();

    return model;
}


void addPlayer(Player p)								//add new player to the DB
{
    QSqlQuery insert(tennisTestDB);

    insert.prepare("INSERT INTO PLAYERS (first_name,last_name,dob,mobile,email,gender_id) VALUES" +toValues(p));
    insert.exec();
    if(insert.isActive())
    {
        qDebug() << " Player Added successfully";
    }
    else
        qDebug() << " Query not active: " << insert.executedQuery() << insert.lastError() << endl;

}

QString toValues(Player p)
{
    return
            "('"+p.firstName+"','" +
            p.lastName+"'," +
            "STR_TO_DATE('"+p.DOB+"','%d/%m/%Y'),'" +
            p.mob+"','" +
            p.email+"','" +
            p.gender_id+"');";
}
void editPlayer(Player p)								//add new player to the DB
{
    QSqlQuery update(tennisTestDB);
    QString query = "UPDATE PLAYERS SET first_name ='"
            + p.firstName   +"',"+
            "last_name ='"   + p.lastName    +"',"+
            "dob = STR_TO_DATE('"+p.DOB+"','%d/%m/%Y')," +
            "mobile ='"      + p.mob         +"',"+
            "email ='"       + p.email       +"',"+
            "gender_id ='"        + p.gender_id        +"'"+
            "WHERE id ="    + p.playerID;
    update.prepare(query);
    update.exec();

    if(update.isActive())
    {
        qDebug() << " Player Edited successfully";
    }
    else
        qDebug() << " Query not active: " << update.lastError() << endl;

}

Player getPlayer(QString id)
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT * FROM PLAYERS WHERE id = "+ id;
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Player Found successfully size";
            return Player(get.value(0).toString(),get.value(1).toString(),get.value(2).toString(),get.value(3).toString(),get.value(4).toString(),get.value(5).toString(),get.value(6).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << endl;
    return Player("","","","","","","");
}

void deletePlayer(QString id)
{                                // Delete player function
    QSqlQuery deleter(tennisTestDB);
    QString query = "DELETE FROM PLAYERS WHERE id = "+ id;
    deleter.prepare(query);
    deleter.exec();

    if(deleter.isActive())
    {

        qDebug() << " Player deleted successfully";
        //TODO close the edit window HINT: make bool

    }
    else
        qDebug() << " Query not active: " << deleter.lastError() << endl;
}

bool verifyPlayer(Player p, bool existingPlayerSearch)
{
    bool exists=true;

    if(existingPlayerSearch)
    {
        QSqlQuery get(tennisTestDB);
        QString query = "SELECT * FROM PLAYERS WHERE id = "+ p.playerID;
        get.prepare(query);
        get.exec();
        if(get.isActive())
        {
            if(!get.first())
            {
                exists = false;
            }
        }
        else
            qDebug() << " Query not active: " << get.lastError() << endl;
    }
    QString errorMessage = "";
    QRegExp emailRX(("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
    bool valid = true;

    if(p.playerID.isEmpty())
    {
        valid = false;
        errorMessage += "ID cannot be empty.\n";
    } else if(!exists)
    {
        valid = false;
        errorMessage += "ID not found.\n";
    }

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

