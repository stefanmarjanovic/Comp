#include "compselector.h"
#include "ui_compselector.h"

CompSelector::CompSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompSelector)
{
    ui->setupUi(this);
    ui->searchTable->setModel(Database::search("competition",""));
    ui->searchTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    IDIndex = Database::getIndex("id", ui->searchTable->model());

    qDebug() << IDIndex;
}

CompSelector::~CompSelector()
{
    delete ui;
}

void CompSelector::on_searchText_textChanged(const QString &arg1)
{
    ui->searchTable->setModel(Database::search("competition", "WHERE (name LIKE '%"+arg1+"%')"));

}


void CompSelector::on_add_clicked()
{
    QModelIndexList selection = ui->searchTable->selectionModel()->selectedIndexes();
    if(!selection.isEmpty())
    {
        emit sendID(selection.at(IDIndex).data().toString());
        CompSelector::close();
    }
}

void CompSelector::on_cancel_clicked()
{
    CompSelector::close();
}
