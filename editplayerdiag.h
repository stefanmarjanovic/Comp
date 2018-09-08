#ifndef EDITPLAYERDIAG_H
#define EDITPLAYERDIAG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDate>

#include "datepick.h"
#include "familysearchdiag.h"


namespace Ui {
class EditPlayerDiag;
}

class EditPlayerDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditPlayerDiag(QWidget *parent = 0);
    ~EditPlayerDiag();

private slots:
    void getDate(const QString text);
    void on_search_clicked();
    void on_apply_clicked();
    void on_deleteButton_clicked();
    void on_cal_clicked();

    void on_cancel_clicked();
    void getFamilyID(QString);

    void on_famSearch_clicked();

public slots:
    void search(QString id);

signals:
    void sendRefresh();
private:
    Ui::EditPlayerDiag *ui;
    DatePick * datepick;
    FamilySearchDiag * familysearchdiag;

};

#endif // EDITPLAYERDIAG_H
