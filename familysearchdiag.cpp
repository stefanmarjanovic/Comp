#include "familysearchdiag.h"
#include "ui_familysearchdiag.h"

FamilySearchDiag::FamilySearchDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FamilySearchDiag)
{
    ui->setupUi(this);
}

FamilySearchDiag::~FamilySearchDiag()
{
    delete ui;
}
