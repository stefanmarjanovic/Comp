#ifndef REFINE_H
#define REFINE_H

#include <QDialog>
#include <QSqlQueryModel>
#include "datepick.h"

namespace Ui {
class Refine;
}

class Refine : public QDialog
{
    Q_OBJECT

public:
    explicit Refine(QWidget *parent = 0);
    ~Refine();


private slots:

    void on_search_clicked();
    void on_searchByID_clicked();

    void on_custom_clicked();

    void on_clear_clicked();

    void on_cancel_clicked();

    void on_cal_2_clicked();

    void on_cal_clicked();
    void getDateFrom(QString text);
    void getDateTo(QString text);

signals:
    void sendWhereQuery(QString);

private:
    Ui::Refine *ui;
    DatePick * datepick;
};

#endif // REFINE_H
