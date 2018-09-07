#ifndef FAMILYSEARCHDIAG_H
#define FAMILYSEARCHDIAG_H

#include <QDialog>

namespace Ui {
class FamilySearchDiag;
}

class FamilySearchDiag : public QDialog
{
    Q_OBJECT

public:
    explicit FamilySearchDiag(QWidget *parent = 0);
    ~FamilySearchDiag();

private:
    Ui::FamilySearchDiag *ui;
};

#endif // FAMILYSEARCHDIAG_H
