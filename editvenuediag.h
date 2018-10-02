#ifndef EDITVENUEDIAG_H
#define EDITVENUEDIAG_H

#include <QDialog>
#include "venue.h"

namespace Ui {
class EditVenueDiag;
}

class EditVenueDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditVenueDiag(QWidget *parent = 0);
    ~EditVenueDiag();

private slots:
    void on_apply_clicked();

    void on_deleteButton_clicked();

    void on_cancel_clicked();

    void on_search_clicked();
public slots:
    void search(QString venueID);

signals:
    void sendRefresh(QString);

private:
    Ui::EditVenueDiag *ui;
};

#endif // EDITVENUEDIAG_H
