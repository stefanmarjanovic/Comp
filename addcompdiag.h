#ifndef ADDCOMPDIAG_H
#define ADDCOMPDIAG_H

#include <QDialog>
#include "datepick.h"
#include "divisionselector.h"

namespace Ui {
class AddCompDiag;
}

class AddCompDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompDiag(QWidget *parent = 0);
    ~AddCompDiag();

private slots:
    void on_cal_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_divisionSearch_clicked();

private:
    Ui::AddCompDiag *ui;
    DatePick * datepick;
    DivisionSelector *divisionselector;

};

#endif // ADDCOMPDIAG_H
