#ifndef ADDPLAYERDIAG_H
#define ADDPLAYERDIAG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "datepick.h"



namespace Ui {
class AddPlayerDiag;
}

class AddPlayerDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayerDiag(QWidget *parent = 0);
    ~AddPlayerDiag();

private slots:
    void getDate(const QString text);
    void on_apply_clicked();

    void on_cancel_clicked();

    void on_cal_clicked();
signals:
    void sendRefresh();
private:
    Ui::AddPlayerDiag *ui;
    DatePick * datepick;
};

#endif // ADDPLAYERDIAG_H
