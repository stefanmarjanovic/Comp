#ifndef ADDDIVISIONDIAG_H
#define ADDDIVISIONDIAG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <QMessageBox>
#include "compselector.h"
#include "datepick.h"
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
    void getCompID(QString id);
    void on_compSearch_clicked();

signals:
    void sendRefresh(QString);

private:
    Ui::addDivisionDiag *ui;
    CompSelector * compselect;
    DatePick * datepick;
};

#endif // ADDDIVISIONDIAG_H
