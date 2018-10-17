#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

#include "settings.h"
namespace Ui {
class Database;
}
class Database : public QObject
{
    Q_OBJECT
public:
public slots:
    static void dbOpen();
    static void dbClose();
    static QSqlQueryModel* search(QString table, QString where);
    static QStringList search(QString table, QString select, QString where);
    static QSqlQueryModel* modelSearch(QString table, QString select, QString where);

    static bool rawQuery(QString query);
    static int getIndex(QString column, QAbstractItemModel *model);
    static bool test(QString host, QString name, QString user, QString password);
    static QStringList customSearch(QString query);
};

#endif // DATABASE_H
