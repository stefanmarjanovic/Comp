#include "adddivisiondiag.h"
#include "ui_adddivisiondiag.h"

addDivisionDiag::addDivisionDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDivisionDiag)
{
    ui->setupUi(this);
}

addDivisionDiag::~addDivisionDiag()
{
    delete ui;
}

void addDivisionDiag::getDivID(QString id)
{
    ui->compID->setText(id);
}

void addDivisionDiag::on_buttonBox_accepted()
{
    QString fname, cID;
    division *d = new division();

    fname = ui->divName->text();
    cID = ui->compID->text();

    d->divName = fname;
    d->compId = cID;
    qDebug() << " Division name: " << d->divName;
    qDebug() << " Comp Id: " << d->compId;


    if(division::verifyName(d->divName) == false && !cID.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
        {
            //Save was clicked
            d->addDivision(*d);
            emit sendRefresh("DIVISION");
            qDebug() << "Saved successfully";

            addDivisionDiag::close();
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

void addDivisionDiag::on_compSearch_clicked()
{
    compselect = new CompSelector(this);
    compselect->show();


    QObject::connect(compselect, SIGNAL(sendID(QString)),this,SLOT(getDivID(QString)));
}


