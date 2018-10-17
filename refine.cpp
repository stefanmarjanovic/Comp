#include "refine.h"
#include "ui_refine.h"
#include "mainwindow.h"

#include "player.h"

Refine::Refine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Refine)
{
    ui->setupUi(this);
}

Refine::~Refine()
{
    delete ui;
}

void Refine::on_search_clicked()
{
    QString gender;

    bool emptyQuery = true;
    QString where = "";

    if(ui->male->isChecked())
        gender = "1";
    if(ui->female->isChecked())
        gender = "0";

    if(!ui->fName->text().isEmpty())
    {
        where += "first_name = '" + ui->fName->text() + "'";
        emptyQuery = false;
    }
    if(!ui->lName->text().isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "last_name = '" + ui->lName->text() + "'";
        emptyQuery = false;
    }

    if(!ui->dobFrom->text().isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "dob > STR_TO_DATE('"+ui->dobFrom->text()+"','%d/%m/%Y')";
        emptyQuery = false;
    }
    if(!ui->dobTo->text().isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "dob < STR_TO_DATE('"+ui->dobTo->text()+"','%d/%m/%Y')";
        emptyQuery = false;
    }

    if(!ui->mob->text().isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "mobile = '" + ui->mob->text() + "'";
        emptyQuery = false;

    }
    if(!ui->email->text().isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "email = '" + ui->email->text() + "'";
        emptyQuery = false;
    }
    if(!gender.isEmpty())
    {
        if(!emptyQuery)
            where += " AND ";
        where += "gender_id = '" + gender + "'";
        emptyQuery = false;

    }
    if(!emptyQuery)
    {
        where.prepend("(");
        where += ")";
    }
    emit sendWhereQuery(where);
    Refine::close();
}

void Refine::on_searchByID_clicked()
{
    QString where = "";
    if(!ui->id->text().isEmpty())
        where = "(id = " + ui->id->text() + ")";
    emit sendWhereQuery(where);

    Refine::close();
}

void Refine::on_custom_clicked()
{
    QString where = "";
    if (!ui->whereStatement->toPlainText().isEmpty())
        where = " (" + ui->whereStatement->toPlainText() + ")";
    emit sendWhereQuery(where);
    Refine::close();
}

void Refine::on_clear_clicked()
{
    ui->dobFrom->clear();
    ui->dobTo->clear();
    ui->email->clear();
    ui->fName->clear();
    ui->lName->clear();
    ui->mob->clear();

    ui->male->setAutoExclusive(false);
    ui->male->setChecked(false);
    ui->male->setAutoExclusive(true);

    ui->female->setAutoExclusive(false);
    ui->female->setChecked(false);
    ui->female->setAutoExclusive(true);
}

void Refine::on_cancel_clicked()
{
    Refine::close();
}

void Refine::on_cal_clicked()
{
    ui->search->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();

    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDateFrom(QString)) );
}

void Refine::on_cal_2_clicked()
{
    ui->search->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();

    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDateTo(QString)) );
}

void Refine::getDateFrom(QString text)
{
    ui->search->setEnabled(true);
    ui->dobFrom->setText(text);

}
void Refine::getDateTo(QString text)
{
    ui->search->setEnabled(true);
    ui->dobTo->setText(text);

}
