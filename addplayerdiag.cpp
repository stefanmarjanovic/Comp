#include "addplayerdiag.h"
#include "ui_addplayerdiag.h"
#include "player.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateEdit>

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
    bool valid = true;
    QString errorMessage = "";

    QRegExp emailRX(("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
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

    for (QChar c : fname)        //string validation
            {
                if(!c.isLetter())
                {
                    valid = false;
                    errorMessage += "First Name Invalid.\n";
                    break;
                }
            }
    for (QChar c : lname)        //string validation
            {
                if(!c.isLetter())
                {
                    valid = false;
                    errorMessage += "Last Name Invalid.\n";
                    break;
                }
            }
    if(mob.length() == 10)
         for (QChar c : mob)        //string validation
            {
                if(!c.isNumber())
                {
                    valid = false;
                    errorMessage += "Mobile Invalid Characters.\n";
                    break;
                }
            }
    else
    {
        valid = false;
        errorMessage += "Mobile Invalid Length.\n";
    }

    if(!emailRX.exactMatch(email))
    {
        valid = false;
        errorMessage += "Email Invalid.\n";

    }

    qDebug() << errorMessage;
    //TODO proper id
    if(valid)
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
            //TODO proper id
            addPlayer("-1",fname,lname,dob,mob,email,gender);
            AddPlayerDiag::close();
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
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(errorMessage);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }


}

void AddPlayerDiag::on_pushButton_2_clicked()
{

    AddPlayerDiag::close();
}

void AddPlayerDiag::on_cal_clicked()
{
    datepick = new DatePick(this);
    datepick->show();
}


