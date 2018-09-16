#ifndef EDITTEAMDIAG_H
#define EDITTEAMDIAG_H

#include <QDialog>

namespace Ui {
class EditTeamDiag;
}

class EditTeamDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditTeamDiag(QWidget *parent = 0);
    ~EditTeamDiag();

private:
    Ui::EditTeamDiag *ui;
};

#endif // EDITTEAMDIAG_H
