#ifndef ADDPLAYERDIAG_H
#define ADDPLAYERDIAG_H

#include <QDialog>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddPlayerDiag *ui;
};

#endif // ADDPLAYERDIAG_H
