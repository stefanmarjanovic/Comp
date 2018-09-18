#ifndef TEAMSEARCHDIAG_H
#define TEAMSEARCHDIAG_H

#include <QDialog>

namespace Ui {
class TeamSearchDiag;
}

class TeamSearchDiag : public QDialog
{
    Q_OBJECT

public:
    explicit TeamSearchDiag(QWidget *parent = 0);
    ~TeamSearchDiag();

private:
    Ui::TeamSearchDiag *ui;
};

#endif // TEAMSEARCHDIAG_H
