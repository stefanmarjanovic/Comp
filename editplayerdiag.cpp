#include "editplayerdiag.h"
#include "ui_editplayerdiag.h"
#include "player.h"

/* GLOBAL VARIABLES */

QString id;

EditPlayerDiag::EditPlayerDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPlayerDiag)
{
    ui->setupUi(this);
}

EditPlayerDiag::~EditPlayerDiag()
{
    delete ui;
}


void EditPlayerDiag::on_search_clicked()
{
    id = ui->id->text();
    Player foundPlayer = getPlayer(id);
    QString dob = QDate::fromString(foundPlayer.DOB,"yyyy-MM-dd").toString("dd/MM/yyyy");
    qDebug() << foundPlayer.type;

    ui->fName->setText(foundPlayer.firstName);
    ui->lName->setText(foundPlayer.lastName);
    ui->dob->setText(dob);
    ui->email->setText(foundPlayer.email);
    ui->mob->setText(foundPlayer.mob);

    if(foundPlayer.type == "1")
        ui->male->setChecked(true);
    else if(foundPlayer.type == "0")
        ui->female->setChecked(true);



    //ui->->setText(foundPlayer.type);


}

void EditPlayerDiag::on_apply_clicked()     //identical to addplayer
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

    Player tempP = Player(id,fname,lname,dob,mob,email,gender);
    if(verifyPlayer(tempP,true))
    {
        QMessageBox msgBox;
        msgBox.setText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
        {
            //TODO proper id
            editPlayer(tempP);
            emit sendRefresh();

            // Save was clicked
            EditPlayerDiag::close();
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

void EditPlayerDiag::on_deleteButton_clicked()
{
    deletePlayer(id);
    emit sendRefresh();

}

void EditPlayerDiag::on_cal_clicked()
{
    datepick = new DatePick(this);
    datepick->show();

    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}

void EditPlayerDiag::getDate(QString text)
{
   ui->dob->setText(text);
}

void EditPlayerDiag::on_cancel_clicked()
{
    EditPlayerDiag::close();
}
