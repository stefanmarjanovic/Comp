#include "venueselector.h"
#include "ui_venueselector.h"

VenueSelector::VenueSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VenueSelector)
{
    ui->setupUi(this);
    ui->searchTable->setModel(Database::search("venue",""));
    ui->searchTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    IDIndex = Database::getIndex("id", ui->searchTable->model());

    qDebug() << IDIndex;

}

VenueSelector::~VenueSelector()
{
    delete ui;
}


void VenueSelector::on_searchText_textChanged(const QString &arg1)
{
    ui->searchTable->setModel(Database::search("venue", "WHERE (name LIKE '%"+arg1+"%')"));

}

void VenueSelector::on_cancel_clicked()
{
    VenueSelector::close();
}

void VenueSelector::on_submit_clicked()
{
    QModelIndexList selection = ui->searchTable->selectionModel()->selectedIndexes();
    if(!selection.isEmpty())
    {
        emit sendID(selection.at(IDIndex).data().toString());
        VenueSelector::close();
    }
}

void VenueSelector::on_pushButton_clicked()
{
    venueselector = new AddVenueDiag(this);
    venueselector->open();


}

