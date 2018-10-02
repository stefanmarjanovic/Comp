#ifndef ADDVENUEDIAG_H
#define ADDVENUEDIAG_H

#include <QDialog>
#include <QDebug>
#include "venue.h"

namespace Ui {
class AddVenueDiag;
}

class AddVenueDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddVenueDiag(QWidget *parent = 0);
    ~AddVenueDiag();

private slots:
    void on_apply_clicked();

    void on_cancel_clicked();

signals:
    void sendRefresh(QString);

private:
    Ui::AddVenueDiag *ui;
};

#endif // ADDVENUEDIAG_H
