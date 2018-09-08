#ifndef FAMILYSEARCHDIAG_H
#define FAMILYSEARCHDIAG_H

#include <QDialog>
#include <QDebug>
#include <player.h>
#include <QModelIndex>

namespace Ui {
class FamilySearchDiag;
}

class FamilySearchDiag : public QDialog
{
    Q_OBJECT

public:
    explicit FamilySearchDiag(QWidget *parent = 0);
    ~FamilySearchDiag();

private slots:
    void on_lname_textChanged(const QString &arg1);

    void on_add_clicked();
signals:
    void sendFamilyID(QString);

private:
    Ui::FamilySearchDiag *ui;
};

#endif // FAMILYSEARCHDIAG_H
