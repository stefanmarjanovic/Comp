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
    /*
    if(!ui->dobFrom->text().isEmpty())
        query += "first_name = '" + ui->fName->text() + "'";
    if(!ui->dobTo->text().isEmpty())
        query += "first_name = '" + ui->fName->text() + "'";
*/

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
        where += "type = '" + gender + "'";
        emptyQuery = false;

    }
    if(!emptyQuery)
    {
        where.prepend(" WHERE (");
        where += ")";
    }
    emit sendSearchResult(search(where));
}

void Refine::on_searchByID_clicked()
{
    QString where = "";
    if(!ui->id->text().isEmpty())
        where = " WHERE (id = " + ui->id->text() + ")";
    emit sendSearchResult(search(where));


}

void Refine::on_custom_clicked()
{
    QString where = "";
    if (!ui->whereStatement->toPlainText().isEmpty())
        where = " WHERE (" + ui->whereStatement->toPlainText() + ")";
    emit sendSearchResult(search(where));
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
