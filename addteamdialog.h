#ifndef ADDTEAMDIALOG_H
#define ADDTEAMDIALOG_H

#include <QDialog>

namespace Ui {
class addTeamDialog;
}

class addTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addTeamDialog(QWidget *parent = 0);
    ~addTeamDialog();

private:
    Ui::addTeamDialog *ui;
};

#endif // ADDTEAMDIALOG_H
