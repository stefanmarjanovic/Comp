#ifndef EDITCOMPDIAG_H
#define EDITCOMPDIAG_H

#include <QDialog>
#include <QDate>

#include "database.h"
#include "datepick.h"
namespace Ui {
class EditCompDiag;
}

class EditCompDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditCompDiag(QWidget *parent = 0);
    ~EditCompDiag();

public slots:
    void search(QString id, QString n);
private slots:
    void on_search_clicked();

    void on_apply_clicked();

    void on_cancel_clicked();

    void on_deleteButton_clicked();

    void on_cal_clicked();

    void getDate(QString d);

signals:
    void sendRefresh(QString);

private:
    Ui::EditCompDiag *ui;
    QString globalID, name, dob, rounds;
    DatePick *datepick;
};

#endif // EDITCOMPDIAG_H
