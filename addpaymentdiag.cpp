#include "addpaymentdiag.h"
#include "ui_addpaymentdiag.h"

extern QSqlDatabase tennisTestDB;
AddPaymentDiag::AddPaymentDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPaymentDiag)
{
    ui->setupUi(this);
    ui->totalLabel->hide();

    //dynamically set combobox from DB(fee.fee_type)
    QSqlQueryModel *modal = new QSqlQueryModel();

    QSqlQuery get(tennisTestDB);
    QString query = "SELECT fee_type FROM fees;";
    get.prepare(query);
    get.exec();
    modal->setQuery(query);

    ui->comboBox->setModel(modal);
}

AddPaymentDiag::~AddPaymentDiag()
{
    delete ui;
}

void AddPaymentDiag::getDate(QString d)
{
    ui->buttonBox->setEnabled(true);
   ui->pDate->setText(d);
}


void AddPaymentDiag::on_cal_clicked()
{
    //ui->apply->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();
    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}


void AddPaymentDiag::on_playerSearch_clicked()
{
    playerselector = new PlayerSelector(this);
    playerselector->open();

    QObject::connect(playerselector, SIGNAL(sendID(QString)),this,SLOT(getPlayerID(QString)));
}

void AddPaymentDiag::getPlayerID(QString id)
{
    ui->playerID->setText(id);
}


void AddPaymentDiag::on_comboBox_currentIndexChanged(const QString &arg1)
{

    //create and store data dynamically for fees table
    QSqlTableModel *fees_table = new QSqlTableModel;
    fees_table->setTable("fees");
    fees_table->select();

    QString fee = ui->comboBox->currentText();

    for(int i = 0; i < fees_table->rowCount(); i++)
    {
        if(fees_table->data(fees_table->index(i,1)).toString() == fee)
        {
            fee = fees_table->data(fees_table->index(i,2)).toString();       //match dropdown text with database row
        }
    }

    ui->totalLabel->setText("Total Due: $" + fee);
    ui->totalLabel->show();

}

void AddPaymentDiag::on_apply_clicked()
{
    QString pId, sdate, paid, regId, feeId;
        QDate cDate, sDate;
        Payment *p = new Payment();

        //create and store data dynamically for fees table
        QSqlTableModel *fees_table = new QSqlTableModel;
        fees_table->setTable("fees");
        fees_table->select();

        //pull user input from dialogue box
        pId = ui->playerID->text();
        sdate = ui->pDate->text();
        paid = ui->amountPaid->text();
        regId = ui->comboBox->currentText();

        //Get dates
        cDate = QDate::currentDate();
        sDate = QDate::fromString(sdate, "dd/MM/yyyy");

        for(int i = 0; i < fees_table->rowCount(); i++)
        {
            if(fees_table->data(fees_table->index(i,1)).toString() == regId)
            {
                regId = fees_table->data(fees_table->index(i,0)).toString();       //match dropdown text with database row
            }
        }

        p->refPlayerID = pId;
        p->currentDate = cDate.toString("yyyy-MM-d");
        p->startdate = sDate.toString("yyyy-MM-d");                     //Payment rego starts from this date
        p->expiryDate = sDate.addYears(1).toString("yyyy-MM-d");        //increment start date by 1 year
        p->amountPaid = paid;
        p->feeId = regId;
        p->calcAmount(p->feeId);                                        //calculate how much is owed

        QString fee = Database::search("fees", "amount", ("id = " + p->feeId)).first();

        if(p != NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("Are you sure?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();

            switch (ret) {
              case QMessageBox::Save:
            {
                //Save was clicked
                p->addPayment(*p);
                //emit sendRefresh("PAYMENT");
                qDebug() << "Saved successfully";

                AddPaymentDiag::close();
                break;
            }
              case QMessageBox::Cancel:
                  // Cancel was clicked
                  break;
              default:
                  // should never be reached
                  break;
            }
        }
}

void AddPaymentDiag::on_cancel_clicked()
{
    AddPaymentDiag::close();
}
