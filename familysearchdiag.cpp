#include "familysearchdiag.h"
#include "ui_familysearchdiag.h"

int family_IDIndex = 0;
FamilySearchDiag::FamilySearchDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FamilySearchDiag)
{
    ui->setupUi(this);
    ui->searchTable->setModel(Player::search(""));
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
        where = "WHERE (last_name LIKE '"+arg1+"%')";
        ui->searchTable->setModel(Player::search(where));
    }
    else
    {
        where = "WHERE (street LIKE '"+arg1+"%')";
        ui->searchTable->setModel(Player::familySearch(where));
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
        ui->searchTable->setModel(Player::search(""));
    }
    else
    {
        ui->searchLabel->setText("Street: ");
        ui->searchTable->setModel(Player::familySearch(""));
    }

    family_IDIndex = FamilySearchDiag::getFamilyIDIndex();

}
