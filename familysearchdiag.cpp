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

    for(int i = 0; i < ui->searchTable->model()->columnCount(); i++)
    {
      if(ui->searchTable->model()->headerData(i, Qt::Horizontal).toString() == "family_id")
          family_IDIndex = i;
    }
    qDebug() << family_IDIndex;
}

FamilySearchDiag::~FamilySearchDiag()
{
    delete ui;
}


void FamilySearchDiag::on_lname_textChanged(const QString &arg1)
{
    QString where = "WHERE (last_name LIKE '"+arg1+"%')";
    ui->searchTable->setModel(Player::search(where));
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
