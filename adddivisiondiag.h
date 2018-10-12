#ifndef ADDDIVISIONDIAG_H
#define ADDDIVISIONDIAG_H

#include <QDialog>
#include <QObject>
#include <QMessageBox>
#include "compselector.h"
#include "division.h"



namespace Ui {
class addDivisionDiag;
}

class addDivisionDiag : public QDialog
{
    Q_OBJECT

public:
    explicit addDivisionDiag(QWidget *parent = 0);
    ~addDivisionDiag();


private slots:
    void on_buttonBox_accepted();

    void getDivID(QString id);

    void on_compSearch_clicked();

private:
    Ui::addDivisionDiag *ui;
    CompSelector * compselect;
};

#endif // ADDDIVISIONDIAG_H
