#include "competition.h"

extern QSqlDatabase tennisTestDB;
Competition::Competition()  //generic constructor
{
        id = 0;

        division = 0;
        rounds = 0;
        boxes = 0;
        teams = 0;

        name = " ";
        startDate = "";
        finishDate = "";
        year = "";

        teamIds = new int[teams];
}

void Competition::addNewComp(){


}

void Competition::addMatch(int r, int c, int val)
{
    this->draw[r][c] = val;
}

int Competition::getTeamById(int i)							//get teams by ID
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT * FROM COMPETITION WHERE id = "+ id;
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Competition Found successfully: ";
            //return Player(get.value(0).toString(),get.value(1).toString(),get.value(2).toString(),get.value(3).toString(),get.value(4).toString(),get.value(5).toString(),get.value(6).toString(),get.value(7).toString());
            return Competition();
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << endl;
    //return Player("","","","","","","","");
    return Competition();
}

Player getPlayer(QString id)
{

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Player Found successfully: ";
            return Player(get.value(0).toString(),get.value(1).toString(),get.value(2).toString(),get.value(3).toString(),get.value(4).toString(),get.value(5).toString(),get.value(6).toString(),get.value(7).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << endl;
    return Player("","","","","","","","");
}
