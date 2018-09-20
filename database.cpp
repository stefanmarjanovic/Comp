#include "database.h"

QSqlDatabase tennisTestDB = QSqlDatabase::addDatabase("QMYSQL");


void Database::dbOpen()
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

void Database::dbClose()
{
    tennisTestDB.close();
}

QSqlQueryModel* Database::search(QString table, QString where)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery search(tennisTestDB);

    search.prepare("SELECT * FROM "+table + " " + where);
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

int Database::getIndex(QString column, QAbstractItemModel *model)
{
    for(int i = 0; i < model->columnCount(); i++)
    {
      if(model->headerData(i, Qt::Horizontal).toString() == column)
          return i;
    }
}
