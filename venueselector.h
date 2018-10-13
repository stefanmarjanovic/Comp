#ifndef VENUESELECTOR_H
#define VENUESELECTOR_H

#include <QDialog>
#include <database.h>
#include "addvenuediag.h"

namespace Ui {
class VenueSelector;
}

class VenueSelector : public QDialog
{
    Q_OBJECT

public:
    explicit VenueSelector(QWidget *parent = 0);
    ~VenueSelector();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_cancel_clicked();

    void on_submit_clicked();

    void on_pushButton_clicked();

signals:
    void sendID(QString);

private:
    Ui::VenueSelector *ui;
    AddVenueDiag *venueselector;
    int IDIndex;

};

#endif // VENUESELECTOR_H
