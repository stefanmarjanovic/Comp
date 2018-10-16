#include "familysearchdiag.h"
#include "ui_familysearchdiag.h"

int family_IDIndex = 0;
FamilySearchDiag::FamilySearchDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FamilySearchDiag)
{
    ui->setupUi(this);
    FamilySearchDiag::on_playerTableRadio_toggled(true);
    ui->searchTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    family_IDIndex = FamilySearchDiag::getFamilyIDIndex();

    qDebug() << family_IDIndex;
}

FamilySearchDiag::~FamilySearchDiag()
{
    delete ui;
}

int FamilySearchDiag::getFamilyIDIndex()
{
    for(int i = 0; i < ui->searchTable->model()->columnCount(); i++)
    {
      if(ui->searchTable->model()->headerData(i, Qt::Horizontal).toString() == "family_id")
          return i;
    }
}

void FamilySearchDiag::on_lname_textChanged(const QString &arg1)
{
    QString where;
    if(ui->playerTableRadio->isChecked())
    {
        where = "(last_name LIKE '"+arg1+"%')";
        ui->searchTable->setModel(Database::modelSearch("PLAYER","ID, first_name as 'First Name', last_name as 'Last Name', dob as 'Date of Birth', Mobile, eMail, Type, family_id, team_id as 'Team ID', case when gender_id = 0 then 'male' when gender_id = 1 then 'female' end as gender",where));
    }
    else
    {
        where = "(street LIKE '"+arg1+"%')";
        ui->searchTable->setModel(Database::modelSearch("FAMILY INNER JOIN SUBURB ON FAMILY.suburdID = SUBURB.ID INNER JOIN STATE ON FAMILY.stateID = STATE.id","family_id, streetNum as 'Street Number', Street, Postcode, resPhone as 'Phone Number', Suburb.suburb_name as Suburb, State.State",where));
    }
}

void FamilySearchDiag::on_add_clicked()
{
    QModelIndexList selection = ui->searchTable->selectionModel()->selectedIndexes();
    if(!selection.isEmpty())
    {
        emit sendFamilyID(selection.at(family_IDIndex).data().toString());
        FamilySearchDiag::close();
    }
}

void FamilySearchDiag::on_newFamily_clicked()
{
    emit sendFamilyID(Player::newFamilyID());
    FamilySearchDiag::close();

}

void FamilySearchDiag::on_playerTableRadio_toggled(bool checked)
{
    qDebug() << "toggletest";
    ui->lname->setText("");
    if(checked)
    {
        ui->searchLabel->setText("Last Name: ");
        ui->searchTable->setModel(Database::modelSearch("PLAYER","ID, first_name as 'First Name', last_name as 'Last Name', dob as 'Date of Birth', Mobile, eMail, Type, family_id, team_id as 'Team ID', case when gender_id = 0 then 'male' when gender_id = 1 then 'female' end as gender",""));
    }
    else
    {
        ui->searchLabel->setText("Street: ");
        ui->searchTable->setModel(Database::modelSearch("FAMILY INNER JOIN SUBURB ON FAMILY.suburdID = SUBURB.ID INNER JOIN STATE ON FAMILY.stateID = STATE.id","family_id, streetNum as 'Street Number', Street, Postcode, resPhone as 'Phone Number', Suburb.suburb_name as Suburb, State.State",""));
    }

    family_IDIndex = FamilySearchDiag::getFamilyIDIndex();

}

void FamilySearchDiag::on_cancel_clicked()
{
    FamilySearchDiag::close();
}
