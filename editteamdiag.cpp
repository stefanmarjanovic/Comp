#include "editteamdiag.h"
#include "ui_editteamdiag.h"

EditTeamDiag::EditTeamDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeamDiag)
{
    ui->setupUi(this);
}

EditTeamDiag::~EditTeamDiag()
{
    delete ui;
}
