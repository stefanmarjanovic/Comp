#include "addplayerdiag.h"
#include "ui_addplayerdiag.h"

#include "mainwindow.h"

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


void AddPlayerDiag::on_apply_clicked()
{
    //TODO REGEX
    QString fname, lname, dob, mob, email, gender, familyID;
    bool male;

    fname = ui->fName->text();
    lname = ui->lName->text();
    dob = ui->dob->text();
    mob = ui->mob->text();
    email = ui->email->text();
    male = ui->male->isChecked();
    familyID = ui->familyID->text();

    if(male)
        gender = "1";
    else
        gender = "0";

    Player tempP = Player("-1",fname,lname,dob,mob,email,gender, familyID); //TODO remove id


    //TODO proper id
    if(verifyPlayer(tempP,false))
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
            addPlayer(tempP);
            emit sendRefresh("PLAYER");
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
}

void AddPlayerDiag::on_cancel_clicked()
{
    AddPlayerDiag::close();
}

void AddPlayerDiag::on_cal_clicked()
{
    ui->apply->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();
    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}

void AddPlayerDiag::getDate(QString text)
{
   ui->apply->setEnabled(true);
   ui->dob->setText(text);
   qDebug() << "test";
}



void AddPlayerDiag::on_famSearch_clicked()
{
    familysearchdiag = new FamilySearchDiag(this);
    familysearchdiag->open();

    QObject::connect(familysearchdiag, SIGNAL(sendFamilyID(QString)),this,SLOT(getFamilyID(QString)));
}

void AddPlayerDiag::getFamilyID(QString fID)
{
    ui->familyID->setText(fID);
}
