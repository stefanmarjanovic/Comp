#ifndef DIVISIONSELECTOR_H
#define DIVISIONSELECTOR_H

#include <QDialog>
#include <database.h>
#include "adddivisiondiag.h"

namespace Ui {
class DivisionSelector;
}

class DivisionSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DivisionSelector(QWidget *parent = 0);
    ~DivisionSelector();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_cancel_clicked();

    void on_submit_clicked();

    void on_pushButton_clicked();

signals:
    void sendID(QString);

private:
    Ui::DivisionSelector *ui;
    addDivisionDiag *adddivsiondiag;
    int IDIndex;
};

#endif // DIVISIONSELECTOR_H
