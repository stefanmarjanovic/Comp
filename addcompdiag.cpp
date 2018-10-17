#include "addcompdiag.h"
#include "ui_addcompdiag.h"

AddCompDiag::AddCompDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompDiag)
{
    ui->setupUi(this);
}

AddCompDiag::~AddCompDiag()
{
    emit sendRefresh("COMP");
    delete ui;
}

void AddCompDiag::on_cal_clicked()
{
    //ui->apply->setEnabled(false);
    ui->apply->setEnabled(false);

    datepick = new DatePick(this);
    datepick->show();
    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}

void AddCompDiag::getDate(QString d)
{
    ui->apply->setEnabled(true);
    ui->sDate->setText(d);
}

void AddCompDiag::on_apply_clicked()
{
    QString compName, startDate, rounds;

    compName = ui->compName->text();
    rounds = ui->roundSelector->currentText();
    startDate = ui->sDate->text();

    qDebug() << startDate;
    //finish date 1 week per box
    if(!Database::rawQuery("INSERT INTO COMPETITION (start_date, name, rounds) VALUES(STR_TO_DATE('"+startDate+"','%d/%m/%Y'), '"+ compName+"', '" + rounds+"');"))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Insert into the database has failed, please check for invalid characters.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
        {
            break;
        }
        default:
            // should never be reached
            break;
        }
    }
    else
    {
        delete this;
    }
}

void AddCompDiag::on_cancel_clicked()
{
    delete this;
}
