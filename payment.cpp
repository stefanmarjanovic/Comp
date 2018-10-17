#include "payment.h"

extern QSqlDatabase tennisTestDB;
Payment::Payment()
{
    refPlayerID = "";
    feeId = "";
    cashId = "";
    owing = "";
    amountPaid = "";
    currentDate = "";
    startdate = "";
    expiryDate = "";
    completeTrans = "";
}

Payment::Payment(QString pID, QString paymentType, QString date, QString paid)
{
    refPlayerID = pID;
    feeId = paymentType;
    currentDate = date;
    amountPaid = paid;
}

Payment Payment::getPayment(QString id)
{
    QSqlQuery get(tennisTestDB);
    QString query = "SELECT payment.player_id, fees.id, payment.date_processed, fees.amount, cash_received.CASH_AMOUNT FROM payment JOIN fees ON payment.fee_id = fees.id JOIN cash_received ON payment.cash_id = cash_received.id WHERE payment.player_id = " + id + ";";
    get.prepare(query);
    get.exec();

    if(get.isActive())
    {
        if(get.first())
        {
            qDebug() << " Payment found successfully";
            return Payment(get.value(1).toString(),get.value(2).toString(),get.value(3).toString(), get.value(4).toString());
        }
    }
    else
        qDebug() << " Query not active: " << get.lastError() << " : " + get.executedQuery();
    return Payment("","","","");
}

void Payment::calcAmount(QString fId)    //must be called after paid amount is set
{
    //run query retrieving registration fee
    QString fee = getFee(fId);  //Database::search("fees", "amount", ("id = " + fId)).first();
    qDebug() << "Fee: " <<  fee;

    if(QString::number(this->amountPaid.toDouble()) < QString::number(fee.toDouble())){

        qDebug() << "IF entered";
        this->owing = QString::number(fee.toDouble() - this->amountPaid.toDouble());
        qDebug() << "Owing: " << this->owing;
        this->completeTrans = "0"; //false - IF partial payment
        qDebug() << "Completed: false";

    } else {
        qDebug() << "IF entered";
        this->amountPaid = fee;
        this->owing = "0";
        this->completeTrans = "1"; //true - IF complete payment
        qDebug() << "Completed: true";
    }
}

void Payment::addPayment(Payment p){

    //insert paid and owing amount into Cash_received table
    QSqlQuery insertCash(tennisTestDB);
    insertCash.prepare("INSERT INTO cash_received (CASH_AMOUNT, OUTSTANDING_AMOUNT) VALUES (" + p.amountPaid + ", " + p.owing + ");");
    insertCash.exec();
    if(insertCash.isActive())
    {
        qDebug() << " Cash Payment Added successfully";
    }
    else
        qDebug() << " Query not active: " << insertCash.executedQuery() << insertCash.lastError();

    //retrieve latest cash_id add to payment object
    p.cashId = Database::customSearch("Select id from cash_received").last();
    qDebug() << "Latest Cash reference ID: " << p.cashId;

    //insert payment details into payment table
    QSqlQuery insertPayment(tennisTestDB);
        insertPayment.prepare("INSERT INTO payment(player_id,fee_id,cash_id, date_processed, completed , date_from, date_to) VALUES (" + p.refPlayerID + ", " + p.feeId + "," + p.cashId + ", STR_TO_DATE('" + p.currentDate + "','%Y-%m-%d'), '"+ p.completeTrans +"', STR_TO_DATE('" + p.startdate + "','%Y-%m-%d'), STR_TO_DATE('" + p.expiryDate + "','%Y-%m-%d'));");
        insertPayment.exec();
    if(insertPayment.isActive())
    {
        qDebug() << " Payment Added successfully";
    }
    else
        qDebug() << " Query not active: " << insertPayment.executedQuery() << insertPayment.lastError();
}

QString Payment::getFee(QString pID)
{
    return QString(Database::search("fees","amount","(id = " + pID +")").first());
}
