#include "editcompdiag.h"
#include "ui_editcompdiag.h"

EditCompDiag::EditCompDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCompDiag)
{
    ui->setupUi(this);
}

EditCompDiag::~EditCompDiag()
{
    delete ui;
    emit sendRefresh("COMP");
}

void EditCompDiag::search(QString id, QString n)
{

    if(!id.isEmpty())
    {
        //Search DB on id
        globalID = id;
        ui->id->setText(id);
        if(!Database::search("COMPETITION","name","id = " + id).isEmpty())
        {
            name = Database::search("COMPETITION","name","id = " + id).first();
            dob = QDate::fromString(Database::search("COMPETITION","start_date","id = " + id).first(),"yyyy-MM-dd").toString("dd/MM/yyyy");

            ui->compName->setText(name);
            ui->roundSelector->setCurrentIndex(Database::search("COMPETITION","rounds","id = " + id).first().toInt()-1);
            ui->sDate->setText(dob);
        }
    }
    else if(!n.isEmpty()){
         //Search DB on name
         name = n;
         dob = QDate::fromString(Database::search("COMPETITION","start_date", "name = '" + name + "'").first(),"yyyy-MM-dd").toString("dd/MM/yyyy");
         globalID = Database::search("COMPETITION","id","name = '" + name + "'").first();

         ui->compName->setText(name);
         ui->roundSelector->setCurrentIndex(Database::search("COMPETITION","rounds", "name = '" + name + "'").first().toInt()-1);
         ui->sDate->setText(dob);
         ui->id->setText(globalID);
    }
    else
    {
        //Competition not found
        ui->compName->setText("");
        ui->roundSelector->setCurrentIndex(0);
        ui->sDate->setText("");
    }
}

void EditCompDiag::on_search_clicked()
{
    EditCompDiag::search(ui->id->text(),ui->compName->text());
}

void EditCompDiag::on_apply_clicked()
{ QMessageBox msgBox;
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
    {
        if(Database::rawQuery("UPDATE COMPETITION SET name = '" + ui->compName->text()
                              + "', rounds = " +  ui->roundSelector->currentText()
                              + ", start_date = STR_TO_DATE('"+ui->sDate->text()+"','%d/%m/%Y') WHERE id = " + globalID))
            delete this;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("Insert into the database has failed, please check for invalid characters.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            switch (ret) {
            case QMessageBox::Ok:
            {
                break;
            }
            default:
                // should never be reached
                break;
            }
        }
    }
    case QMessageBox::Cancel:
    {
        break;
    }
    default:
        // should never be reached
        break;
    }
}

void EditCompDiag::on_cancel_clicked()
{
    delete this;
}

void EditCompDiag::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
    {
        if(Database::rawQuery("DELETE FROM COMPETITION WHERE id = " + globalID))
            delete this;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("Insert into the database has failed, please check for invalid characters.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            switch (ret) {
            case QMessageBox::Ok:
            {
                break;
            }
            default:
                // should never be reached
                break;
            }
        }
    }
    case QMessageBox::Cancel:
    {
        break;
    }
    default:
        // should never be reached
        break;
    }
}

void EditCompDiag::on_cal_clicked()
{
    ui->apply->setEnabled(false);

    datepick = new DatePick(this);
    datepick->show();
    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}
void EditCompDiag::getDate(QString d)
{
    ui->apply->setEnabled(true);
    ui->sDate->setText(d);
}

