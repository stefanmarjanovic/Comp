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
}
