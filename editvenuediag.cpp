#include "editvenuediag.h"
#include "ui_editvenuediag.h"

QString venID;

EditVenueDiag::EditVenueDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditVenueDiag)
{
    ui->setupUi(this);
}

EditVenueDiag::~EditVenueDiag()
{
    delete ui;
}

void EditVenueDiag::search(QString venueID)
{
    ui->id_2->setText(venueID);
    on_search_clicked();
}

void EditVenueDiag::on_apply_clicked()
{
    Venue v = Venue(ui->venueName->text(),ui->streetNum->text(),ui->street->text(),ui->suburb->text(),ui->postcode->text());
    if(Venue::verifyVenue(v))
    {
        QMessageBox msgBox;
        msgBox.setText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
        {
            Venue::editVenue(v, venID);
            emit sendRefresh("VENUE");
            EditVenueDiag::close();
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

void EditVenueDiag::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
    {
        Venue::deleteVenue(venID);
        emit sendRefresh("VENUE");

        EditVenueDiag::close();
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

void EditVenueDiag::on_cancel_clicked()
{
    EditVenueDiag::close();
}

void EditVenueDiag::on_search_clicked()
{
    venID = ui->id_2->text();
    Venue v = Venue::getVenue(venID);

    ui->venueName->setText(v.venueName);
    ui->streetNum->setText(v.streetNumber);
    ui->street->setText(v.streetName);
    ui->postcode->setText(v.postcode);
    ui->suburb->setText(Venue::getSuburb(v.suburb));
}
