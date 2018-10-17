#ifndef EDITCOMPDIAG_H
#define EDITCOMPDIAG_H

#include <QDialog>

namespace Ui {
class EditCompDiag;
}

class EditCompDiag : public QDialog
{
    Q_OBJECT

public:
    explicit EditCompDiag(QWidget *parent = 0);
    ~EditCompDiag();

private:
    Ui::EditCompDiag *ui;
};

#endif // EDITCOMPDIAG_H
