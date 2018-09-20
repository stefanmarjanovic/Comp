#ifndef COMPSELECTOR_H
#define COMPSELECTOR_H

#include <QDialog>
#include "database.h"

namespace Ui {
class CompSelector;
}

class CompSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CompSelector(QWidget *parent = 0);
    ~CompSelector();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_add_clicked();

    void on_cancel_clicked();

signals:
    void sendID(QString);

private:
    Ui::CompSelector *ui;
    int IDIndex;
};

#endif // COMPSELECTOR_H
