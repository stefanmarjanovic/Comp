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

    void getDate(QString);

    void on_apply_clicked();

    void on_cancel_clicked();

signals:
    void sendRefresh(QString);

private:
    Ui::AddCompDiag *ui;
    DatePick * datepick;

};

#endif // ADDCOMPDIAG_H
