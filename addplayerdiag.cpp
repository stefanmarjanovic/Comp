#include "addplayerdiag.h"
#include "ui_addplayerdiag.h"
#include "player.h"
#include "mainwindow.h"
#include <QDebug>

AddPlayerDiag::AddPlayerDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlayerDiag)
{
    ui->setupUi(this);
}

AddPlayerDiag::~AddPlayerDiag()
{
    delete ui;
}


void AddPlayerDiag::on_pushButton_clicked()
{
    //TODO REGEX
    QString fname, lname, dob, mob, email, gender;
    bool male;
    fname = ui->fName->text();
    lname = ui->lName->text();
    dob = ui->dob->text();
    mob = ui->mob->text();
    email = ui->email->text();
    male = ui->male->isChecked();

    if(male)
        gender = "1";
    else
        gender = "0";

    QRegExp re("\\c*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(fname))
       qDebug() << "all characters";

    //TODO proper id
    addPlayer("-1",fname,lname,dob,mob,email,gender);
    AddPlayerDiag::close();

}

void AddPlayerDiag::on_pushButton_2_clicked()
{

    AddPlayerDiag::close();
}
