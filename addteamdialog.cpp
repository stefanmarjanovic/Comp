#include "addteamdialog.h"
#include "ui_addteamdialog.h"

addTeamDialog::addTeamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTeamDialog)
{
    ui->setupUi(this);
}

addTeamDialog::~addTeamDialog()
{
    delete ui;
}
