#include "teamsearchdiag.h"
#include "ui_teamsearchdiag.h"

TeamSearchDiag::TeamSearchDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamSearchDiag)
{
    ui->setupUi(this);
}

TeamSearchDiag::~TeamSearchDiag()
{
    delete ui;
}
