#include "team.h"

extern QSqlDatabase tennisTestDB;
Team::Team(QString name, QString division_id, QString comp_id)
{
    this->name = name;
    this->division_id = division_id;
    this->comp_id = comp_id;
}

bool Team::verifyTeam(Team t)
{
    QString errorMessage = "";
    bool valid = true;

    if(t.name.isEmpty())
    {
        valid = false;
        errorMessage += "Team Name Invalid.\n";
    }
    else
        for (QChar c : t.name)        //string validation
        {
            if(!c.isLetter() && c != " ")
            {
                valid = false;
                errorMessage += "Team Name Invalid.\n";
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

void Team::addTeam(Team t)
{
    QSqlQuery insertTeam(tennisTestDB);
    insertTeam.prepare("INSERT INTO team (name, division_id, comp_id) VALUES ('"
                       + t.name     +"','"
                       + t.division_id +"','"
                       + t.comp_id     +"')");
    insertTeam.exec();

    if(insertTeam.isActive())
    {
        qDebug() << " Team Added successfully";
    }
    else
        qDebug() << " Query not active: " << insertTeam.executedQuery() << insertTeam.lastError();
}
void Team::editTeam(Team t, QString id)
{
    QSqlQuery update(tennisTestDB);
    update.prepare("UPDATE TEAM SET name ='" + t.name + "',"+
            "division_id = '" + t.division_id + "',"+
            "comp_id = '" +t.comp_id + "'"+
            "WHERE id = " + id);
    update.exec();

    if(update.isActive())
    {
        qDebug() << " Team Edited successfully";
    }
    else
        qDebug() << " Query not active: " << update.lastError() << endl;

}

QSqlQueryModel* Team::search(QString where)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare("select t.id, t.tablePosition as 'Table Position', t.name as 'Team Name', c.name as 'Competition Name', d.name as 'Division Name' FROM TEAM t LEFT OUTER JOIN COMPETITION c ON c.id = t.comp_id LEFT OUTER JOIN Division d ON d.id = t.division_id "
                   + where
                   + " ORDER BY id;");
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
Team Team::getTeam(QString id)
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT * FROM team WHERE id = '"+ id +"'";
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " team Found successfully size";
            return Team(get.value(1).toString(),get.value(2).toString(),get.value(3).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << " : " + get.executedQuery();
    return Team("","","");


}
void Team::deleteTeam(QString id)
{                                // Delete player function
    QSqlQuery deleter(tennisTestDB);
    QString query = "DELETE FROM team WHERE id = '"+ id + "'";
    deleter.prepare(query);
    deleter.exec();

    if(deleter.isActive())
    {

        qDebug() << " team deleted successfully";
        //TODO close the edit window HINT: make bool

    }
    else
        qDebug() << " Query not active: " << deleter.lastError() << " : " + deleter.executedQuery();


}
