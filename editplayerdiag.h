#ifndef EDITPLAYERDIAG_H
#define EDITPLAYERDIAG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class EditPlayerDiag;
}

class EditPlayerDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditPlayerDiag(QWidget *parent = 0);
    ~EditPlayerDiag();

private slots:
    void on_search_clicked();

    void on_apply_clicked();

    void on_deleteButton_clicked();

private:
    Ui::EditPlayerDiag *ui;
};

#endif // EDITPLAYERDIAG_H
