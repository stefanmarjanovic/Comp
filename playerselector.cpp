#include "playerselector.h"
#include "ui_playerselector.h"

PlayerSelector::PlayerSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerSelector)
{
    ui->setupUi(this);
    ui->searchTable->setModel(Database::search("PLAYER",""));
    ui->searchTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    IDIndex = Database::getIndex("id", ui->searchTable->model());

    qDebug() << IDIndex;
}

PlayerSelector::~PlayerSelector()
{
    delete ui;
}

void PlayerSelector::on_searchPlayer_textChanged(const QString &arg1)
{
      QString where = "WHERE (first_name LIKE '"+arg1+"%' OR last_name LIKE '"+arg1+"%' OR mobile LIKE '"+arg1+"%' OR email LIKE '"+arg1+"%')";
      ui->searchTable->setModel(Database::search("players", where));
}

void PlayerSelector::on_buttonBox_accepted()
{
    QModelIndexList selection = ui->searchTable->selectionModel()->selectedIndexes();
    if(!selection.isEmpty())
    {
        emit sendID(selection.at(IDIndex).data().toString());
        PlayerSelector::close();
    }
}

void PlayerSelector::on_buttonBox_rejected()
{
     PlayerSelector::close();
}
