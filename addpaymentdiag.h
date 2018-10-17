#ifndef ADDPAYMENTDIAG_H
#define ADDPAYMENTDIAG_H

#include <QDialog>
#include <QObject>
#include <QString>
#include <QComboBox>
#include <Qdate>

#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

#include "datepick.h"
#include "payment.h"
#include "playerselector.h"



namespace Ui {
class AddPaymentDiag;
}

class AddPaymentDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddPaymentDiag(QWidget *parent = 0);
    ~AddPaymentDiag();


private slots:
    void getDate(QString d);
    void on_cal_clicked();

    void on_playerSearch_clicked();
    void getPlayerID(QString id);


    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_apply_clicked();

    void on_cancel_clicked();

signals:
    void sendRefresh(QString);


private:
    Ui::AddPaymentDiag *ui;
    DatePick * datepick;
    PlayerSelector * playerselector;

};

#endif // ADDPAYMENTDIAG_H
