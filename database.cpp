#include "database.h"

QSqlDatabase tennisTestDB = QSqlDatabase::addDatabase("QMYSQL");

bool Database::test(QString host, QString name, QString user, QString password)
{
    bool valid = true;
    QString message = "";

    tennisTestDB.setHostName(host);
    tennisTestDB.setDatabaseName(name);
    tennisTestDB.setUserName(user);
    tennisTestDB.setPassword(password);
    if(tennisTestDB.isValid())
    {
        tennisTestDB.open();
        if(!tennisTestDB.isOpen())
        {
            message="Connection failed";
            valid = false;
        }
    }
    else
    {
        valid = false;
        message="Connection failed";
    }

    if (!valid)
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(message);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Success");
        msgBox.setInformativeText("Connected successfully");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    return valid;
}
void Database::dbOpen()
{
    QSettings dbSettings;
    qDebug() << dbSettings.value("changed").toString();
    if(dbSettings.value("changed") != "true")
    {
        dbSettings.setValue("DBHost","127.0.0.1");
        dbSettings.setValue("DBName","tennisTestDB");
        dbSettings.setValue("DBUser","root");
        dbSettings.setValue("DBPassword","");
        dbSettings.setValue("changed","true");

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
    else
    {
        tennisTestDB.setHostName(dbSettings.value("DBHost").toString());
        tennisTestDB.setDatabaseName(dbSettings.value("DBName").toString());
        tennisTestDB.setUserName(dbSettings.value("DBUser").toString());
        if(dbSettings.value("DBPassword") != "")
            tennisTestDB.setUserName(dbSettings.value("DBPassword").toString());
        if(tennisTestDB.isValid())
        {
            tennisTestDB.open();
            if(!tennisTestDB.isOpen())
                qDebug() << "DB from settings not open" << dbSettings.value("DBHost").toString();
        }
        else
            qDebug() << "DB from settings not valid";
    }
}

void Database::dbClose()
{
    QString connection;
    connection = tennisTestDB.connectionName();
    tennisTestDB.close();
    tennisTestDB = QSqlDatabase();
    tennisTestDB.removeDatabase(connection);
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

QStringList Database::search(QString table, QString select, QString where)
{
    QSqlQuery search(tennisTestDB);
    QStringList result;

    search.prepare("SELECT " + select + " FROM " + table + " WHERE " + where);

    search.exec();

    if(search.isActive())
    {
        qDebug() << " Query active: " << search.executedQuery();

        while (search.next())
        {
                QString divID = search.value(0).toString();
                result << divID;
        }

    }
    else
        qDebug() << " Query not active: " << search.executedQuery();

    return result;
}

int Database::getIndex(QString column, QAbstractItemModel *model)
{
    for(int i = 0; i < model->columnCount(); i++)
    {
        if(model->headerData(i, Qt::Horizontal).toString() == column)
            return i;
    }
    return 0;
}

QStringList Database::search(QString table, QString select, QString where)
{
    QSqlQuery search(tennisTestDB);
    QStringList result;

    search.prepare("SELECT " + select + " FROM " + table + " WHERE " + where);

    search.exec();

    if(search.isActive())
    {
        qDebug() << " Query active: " << search.executedQuery();

        while (search.next())
        {
                QString divID = search.value(0).toString();
                result << divID;
        }

    }
    else
        qDebug() << " Query not active: " << search.executedQuery();

    return result;
}

QStringList Database::customSearch(QString query)
{
    QSqlQuery search(tennisTestDB);
    QStringList result;

    search.prepare(query);

    search.exec();

    if(search.isActive())
    {
        qDebug() << " Query active: " << search.executedQuery();

        while (search.next())
        {
                QString divID = search.value(0).toString();
                result << divID;
        }

    }
    else
        qDebug() << " Query not active: " << search.executedQuery();

    return result;
}

