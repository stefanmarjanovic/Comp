#include "editplayerdiag.h"
#include "ui_editplayerdiag.h"
#include "player.h"

/* GLOBAL VARIABLES */

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

void EditPlayerDiag::search(QString playerID)
{
    ui->id->setText(playerID);
    on_search_clicked();
}

void EditPlayerDiag::on_search_clicked()
{
    id = ui->id->text();
    Player foundPlayer = getPlayer(id);
    QString dob = QDate::fromString(foundPlayer.DOB,"yyyy-MM-dd").toString("dd/MM/yyyy");
    qDebug() << foundPlayer.gender_id;

    ui->fName->setText(foundPlayer.firstName);
    ui->lName->setText(foundPlayer.lastName);
    ui->dob->setText(dob);
    ui->email->setText(foundPlayer.email);
    ui->mob->setText(foundPlayer.mob);
    ui->familyID->setText(foundPlayer.FamilyID);

    if(foundPlayer.gender_id == "1")
        ui->male->setChecked(true);
    else if(foundPlayer.gender_id == "0")
        ui->female->setChecked(true);
}

void EditPlayerDiag::on_apply_clicked()     //identical to addplayer
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

    Player tempP = Player(id,fname,lname,dob,mob,email,gender,familyID);
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
            emit sendRefresh("PLAYER");

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
    QMessageBox msgBox;
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
    {
        deletePlayer(id);
        emit sendRefresh("PLAYER");

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

void EditPlayerDiag::on_cal_clicked()
{
    ui->search->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();

    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}

void EditPlayerDiag::getDate(QString text)
{
   ui->search->setEnabled(true);
   ui->dob->setText(text);
}

void EditPlayerDiag::on_cancel_clicked()
{
    EditPlayerDiag::close();
}


void EditPlayerDiag::getFamilyID(QString fID)
{
    ui->familyID->setText(fID);
}


void EditPlayerDiag::on_famSearch_clicked()
{
    familysearchdiag = new FamilySearchDiag(this);
    familysearchdiag->show();

    QObject::connect(familysearchdiag, SIGNAL(sendFamilyID(QString)),this,SLOT(getFamilyID(QString)));
}
