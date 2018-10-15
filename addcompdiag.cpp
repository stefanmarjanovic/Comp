#include "addcompdiag.h"
#include "ui_addcompdiag.h"

AddCompDiag::AddCompDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompDiag)
{
    ui->setupUi(this);
}

AddCompDiag::~AddCompDiag()
{
    delete ui;
}

void AddCompDiag::on_cal_clicked()
{
    //ui->apply->setEnabled(false);
    datepick = new DatePick(this);
    datepick->show();
    QObject::connect(datepick,SIGNAL(sendDate(QString)),this,SLOT(getDate(QString)) );
}

void AddCompDiag::on_buttonBox_accepted()
{
    QString cName, sDate, r;
    QVariant rounds;
    QVector<int> divs, teamIds;

    cName = ui->compName->text();
    rounds = ui->roundSelector->itemData(ui->roundSelector->currentIndex());
    sDate = ui->cal->text();

    //verify input fields are completed
    //pull in division/teams
    //calc boxes per round (no of teams - 1 if even)(no of teams if odd)

    //construct vector matrix
    //construct draw (x no. of rounds)

    //match teamId to team Name
    //display draw
}

void AddCompDiag::on_buttonBox_rejected()
{
    AddCompDiag::close();
}

void AddCompDiag::on_divisionSearch_clicked()
{
    divisionselector = new DivisionSelector(this);
    divisionselector->show();

    QObject::connect(divisionselector, SIGNAL(sendID(QString)),this,SLOT(getDivID(QString)));
}

void AddCompDiag::getDivID(QString id)
{
    ui->divisionID->setText(id);
}

void AddCompDiag::getDate(QString d)
{
    ui->sDate->setText(d);
}
