#ifndef PAYMENT_H
#define PAYMENT_H

#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include "database.h"

class Payment
{

    public:
        Payment();
        Payment(QString pID, QString paymentType, QString date, QString paid);

        QString refPlayerID;        //reference to the player table
        QString feeId;              //reference to fees table
        QString cashId;             //reference to cash_received table
        QString currentDate;        //today's date
        QString owing;              //total amount owed
        QString amountPaid;         //amount paid  
        QString startdate;          //
        QString expiryDate;         //Memnership active from start to expiry date

        static Payment getPayment(QString id);      //return a payment type
        void calcAmount(QString fId);                 //calculate the outstanding amount
        static void addPayment(Payment p);          //add a payment
        static int getFee(QString pID);             //return the cost of the registration fee

};

#endif // PAYMENT_H
