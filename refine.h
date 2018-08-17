#ifndef REFINE_H
#define REFINE_H

#include <QDialog>

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
    void on_pushButton_clicked();

private:
    Ui::Refine *ui;
};

#endif // REFINE_H
