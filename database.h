#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class Database;
}
class Database
{
    Q_OBJECT
public:
public slots:
    static void dbOpen();
    static void dbClose();
    static QSqlQueryModel* search(QString table, QString where);
    static int getIndex(QString column, QAbstractItemModel *model);
};

#endif // DATABASE_H
