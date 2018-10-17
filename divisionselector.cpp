#include "divisionselector.h"
#include "ui_divisionselector.h"


DivisionSelector::DivisionSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DivisionSelector)
{
    ui->setupUi(this);
    ui->divisionTable->setModel(Database::search("division",""));
    ui->divisionTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    IDIndex = Database::getIndex("id", ui->divisionTable->model());

    qDebug() << IDIndex;
}

DivisionSelector::~DivisionSelector()
{
    delete ui;
}

void DivisionSelector::on_searchText_textChanged(const QString &arg1)
{
    ui->divisionTable->setModel(Database::search("division", "WHERE (name LIKE '%"+arg1+"%')"));

}

void DivisionSelector::on_cancel_clicked()
{
    DivisionSelector::close();
}

void DivisionSelector::on_submit_clicked()
{
    QModelIndexList selection = ui->divisionTable->selectionModel()->selectedIndexes();
    if(!selection.isEmpty())
    {
        emit sendID(selection.at(IDIndex).data().toString());
        DivisionSelector::close();
    }
}

void DivisionSelector::on_pushButton_clicked()
{
    adddivsiondiag = new addDivisionDiag(this);
    adddivsiondiag->show();


}
