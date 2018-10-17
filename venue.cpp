#include "venue.h"

extern QSqlDatabase tennisTestDB;
Venue::Venue(QString venueName, QString streetNumber, QString streetName, QString suburb, QString postcode)					//public constructor
{								//Venue constructor
    this->venueName = venueName ;
    this->streetNumber = streetNumber;
    this->streetName = streetName;
    this->suburb = suburb;
    this->postcode = postcode;
}

bool Venue::verifyVenue(Venue v)
{
    QString errorMessage = "";
    bool valid = true;

    if(v.venueName.isEmpty())
    {
        valid = false;
        errorMessage += "Venue Name Invalid.\n";
    }
    else
        for (QChar c : v.venueName)        //string validation
        {
            if(!c.isLetter() && c != " ")
            {
                valid = false;
                errorMessage += "Venue Name Invalid.\n";
                break;
            }
        }


    if(v.streetNumber.isEmpty())
    {
        valid = false;
        errorMessage += "Street Number Invalid.\n";
    }
    else
        for (QChar c : v.streetNumber)        //string validation
        {
            if(!c.isNumber() && c != " ")
            {
                valid = false;
                errorMessage += "Street Number Invalid.\n";
                break;
            }
        }
    if(v.streetName.isEmpty())
    {
        valid = false;
        errorMessage += "Street Name Invalid.\n";
    }
    else
        for (QChar c : v.streetName)        //string validation
        {
            if(!c.isLetter() && c != " ")
            {
                valid = false;
                errorMessage += "Street Name Invalid.\n";
                break;
            }
        }
    if(v.suburb.isEmpty())
    {
        valid = false;
        errorMessage += "Suburb Invalid.\n";
    }
    else
        for (QChar c : v.suburb)        //string validation
        {
            if(!c.isLetter() && c != " ")
            {
                valid = false;
                errorMessage += "Suburb Invalid.\n";
                break;
            }
        }
    if(v.postcode.isEmpty() || v.postcode.length() != 4)
    {
        valid = false;
        errorMessage += "Postcode Invalid.\n";
    }
    else
        for (QChar c : v.postcode)        //string validation
        {
            if(!c.isNumber())
            {
                valid = false;
                errorMessage += "Postcode Invalid.\n";
                break;
            }
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
QString addSuburb(QString suburb)								//add new venue to the DB
{
    QSqlQuery findSuburb(tennisTestDB);
    QSqlQuery insertSuburb(tennisTestDB);

    findSuburb.prepare("Select id FROM suburb WHERE suburb_name = '" + suburb + "'");
    findSuburb.exec();
    if(findSuburb.isActive())
    {
        qDebug() << " Suburb Added/Found successfully";
        if(findSuburb.first())
        {
            return findSuburb.value(0).toString();
        }
        else
        {
            insertSuburb.prepare("INSERT INTO suburb (suburb_name) VALUES ('" + suburb +"');");
            insertSuburb.exec();
            if(insertSuburb.isActive())
            {
                insertSuburb.prepare("SELECT id FROM suburb WHERE ID = @@Identity;");
                insertSuburb.exec();
                if(insertSuburb.isActive())
                {
                    if(insertSuburb.first())
                    {
                        return insertSuburb.value(0).toString();
                    }
                }
                else
                    qDebug() << " Query not active: " << insertSuburb.lastError() << " : " + insertSuburb.executedQuery();
            }
            else
                qDebug() << " Query not active: " << insertSuburb.lastError() << " : " + insertSuburb.executedQuery();
        }
    }
    else
        qDebug() << " Query not active: " << findSuburb.executedQuery() << findSuburb.lastError() << endl;
}

void Venue::addVenue(Venue v)								//add new venue to the DB
{
    QSqlQuery insertVenue(tennisTestDB);
        insertVenue.prepare("INSERT INTO venue (name,street_number,street,suburb_id,postcode) VALUES ('"+v.venueName+"','"
                   + v.streetNumber +"','"
                   + v.streetName +"','"
                   + addSuburb(v.suburb) +"','"
                   + v.postcode +"')");
    insertVenue.exec();
    if(insertVenue.isActive())
    {
        qDebug() << " Venue Added successfully";
    }
    else
        qDebug() << " Query not active: " << insertVenue.executedQuery() << insertVenue.lastError();



}
void Venue::editVenue(Venue v, QString id)								//add new venue to the DB
{
    QSqlQuery update(tennisTestDB);
    QString query = "UPDATE venue SET postcode ='"
            + v.postcode   +"',"+
            "street ='"   + v.streetName    +"',"+
            "street_number ='"      + v.streetNumber         +"',"+
            "suburb_id ='"       + addSuburb(v.suburb)      +"',"+
            "name ='"        + v.venueName        +"'"+
            "WHERE id ="    + id;
    update.prepare(query);
    update.exec();

    if(update.isActive())
    {
        qDebug() << " Player Edited successfully";
    }
    else
        qDebug() << " Query not active: " << update.lastError() << endl;


}

QSqlQueryModel* Venue::search(QString where)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare("SELECT * FROM venue " + where);
    search.exec();

    if(search.isActive())
    {
        model->setQuery(search);
        qDebug() << " Query active: " << search.executedQuery();

    }
    else
        qDebug() << " Query not active: " << search.executedQuery() << " : " + search.executedQuery();

    return model;
}

Venue Venue::getVenue(QString id)
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT * FROM venue WHERE id = '"+ id +"'";
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Venue Found successfully size";
            return Venue(get.value(1).toString(),get.value(2).toString(),get.value(3).toString(),get.value(4).toString(),get.value(5).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << " : " + get.executedQuery();
    return Venue("","","","","");


}

QString Venue::getSuburb(QString id)
{
    QSqlQuery findSuburb(tennisTestDB);

    findSuburb.prepare("SELECT suburb_name FROM suburb WHERE ID = '" + id + "'");
    findSuburb.exec();
    if(findSuburb.isActive())
    {
        if(findSuburb.first())
        {
            return findSuburb.value(0).toString();
        }
    }
    else
        qDebug() << " Query not active: " << findSuburb.lastError() << " : " + findSuburb.executedQuery();

    return "";
}

void Venue::deleteVenue(QString id)
{                                // Delete player function
    QSqlQuery deleter(tennisTestDB);
    QString query = "DELETE FROM venue WHERE id = '"+ id + "'";
    deleter.prepare(query);
    deleter.exec();

    if(deleter.isActive())
    {

        qDebug() << " VENUE deleted successfully";
        //TODO close the edit window HINT: make bool

    }
    else
        qDebug() << " Query not active: " << deleter.lastError() << " : " + deleter.executedQuery();


}

