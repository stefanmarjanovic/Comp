#ifndef ADDTEAMDIALOG_H
#define ADDTEAMDIALOG_H

#include <QDialog>
#include "divisionselector.h"
#include "compselector.h"
#include "team.h"

namespace Ui {
class addTeamDialog;
}

class addTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addTeamDialog(QWidget *parent = 0);
    ~addTeamDialog();

private slots:
    void on_divisionSearch_clicked();

    void on_compSearch_clicked();
    void getDivID(QString);
    void getCompID(QString);


    void on_apply_clicked();
    void on_cancel_clicked();

signals:
    void sendRefresh(QString);
private:
    Ui::addTeamDialog *ui;
    DivisionSelector *divisionselector;
    CompSelector *compselector;
};

#endif // ADDTEAMDIALOG_H
