#include "addvenuediag.h"
#include "ui_addvenuediag.h"

AddVenueDiag::AddVenueDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVenueDiag)
{
    ui->setupUi(this);
}

AddVenueDiag::~AddVenueDiag()
{
    delete ui;
}

void AddVenueDiag::on_apply_clicked()
{
    Venue v = Venue(ui->vName->text(),ui->streetNum->text(),ui->streetName->text(),ui->suburb->text(),ui->postCode->text());

    qDebug() << v.venueName << " " << ui->vName->text();

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
            Venue::addVenue(v);
            emit sendRefresh();
            AddVenueDiag::close();
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

void AddVenueDiag::on_cancel_clicked()
{
    AddVenueDiag::close();
}
