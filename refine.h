#ifndef REFINE_H
#define REFINE_H

#include <QDialog>
#include <QSqlQueryModel>

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

signals:
    void sendSearchResult(QSqlQueryModel*);

private:
    Ui::Refine *ui;
};

#endif // REFINE_H
