#include "editplayerdiag.h"
#include "ui_editplayerdiag.h"
#include "player.h"
#include <QDebug>

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
    Player foundPlayer = getPlayer(ui->id->text());
    qDebug() << foundPlayer.type;

    ui->fName->setText(foundPlayer.firstName);
    ui->lName->setText(foundPlayer.lastName);
    ui->dob->setText(foundPlayer.DOB);
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
    QString id, fname, lname, dob, mob, email, gender;
    bool male;
    id  = ui->id->text();
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

    //TODO proper id
    editPlayer(id,fname,lname,dob,mob,email,gender);
    EditPlayerDiag::close();

}
