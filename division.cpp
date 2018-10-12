#include "division.h"
#include <QChar>

extern QSqlDatabase tennisTestDB;
division::division()
{
    compId = "";
    divName = "";
}

division::division(QString dName)
{
    divName = dName;
}


void division::addDivision(division d)
{
    QSqlQuery insertDiv(tennisTestDB);
        insertDiv.prepare("INSERT INTO division (name) VALUES ('"+d.divName+"')");
        insertDiv.exec();
      if(insertDiv.isActive())
    {
        qDebug() << " Venue Added successfully";
    }
    else
        qDebug() << " Query not active: " << insertDiv.executedQuery() << insertDiv.lastError();
}


division division::getDivision(QString id)
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT * FROM division WHERE id = '"+ id +"'";
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Division Found successfully size";
            return division(get.value(1).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << " : " + get.executedQuery();

    return division("");
}

bool division::verifyName(division d)
{
    QString errorMessage = "";

    if(d.divName.isEmpty()){
        return false;
        errorMessage += "Venue Name Invalid.\n";
    }
    else {
        for(QChar c : d.divName)
        {
            if(!c.isLetter()){
                return false;
                errorMessage += "Venue Name Invalid.\n";
            }
        }
    }

    return true;
}

void division::editDivsion(int id, QString dName){

    QSqlQuery update(tennisTestDB);
    QString query = "UPDATE division SET name ='"        +  dName    +"'WHERE id ="    + id + "'";
    update.prepare(query);
    update.exec();

    if(update.isActive())
    {
        qDebug() << " Division Edited successfully";
    }
    else
        qDebug() << " Query not active: " << update.lastError() << endl;

}

void division::deleteDivision(QString id)
{
        QSqlQuery deleter(tennisTestDB);
        QString query = "DELETE FROM division WHERE id = '"+ id + "'";
        deleter.prepare(query);
        deleter.exec();

        if(deleter.isActive())
        {

            qDebug() << " Division deleted successfully";
            //TODO close the edit window HINT: make bool

        }
        else
            qDebug() << " Query not active: " << deleter.lastError() << " : " + deleter.executedQuery();
}
