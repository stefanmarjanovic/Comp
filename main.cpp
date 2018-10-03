#include "mainwindow.h"
#include <qtsql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QStyleFactory>

#include <QSplashScreen>
#include <qthread.h>

#include <iostream>
using namespace std;

class splashTimer : public QThread
{
public:
    static void sleep(unsigned long secs) { QThread::sleep(secs); }
};

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);

    QPixmap pixmap(":/ACMSplash.PNG");
    QSplashScreen splash(pixmap);
    splash.show();

    splashTimer::sleep(5); // splash is shown for 5 seconds

    MainWindow w;
    w.show();


    splash.finish(&w);
    return a.exec();
}
