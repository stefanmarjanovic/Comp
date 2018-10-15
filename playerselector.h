#ifndef PLAYERSELECTOR_H
#define PLAYERSELECTOR_H

#include <QDialog>
#include "database.h"

namespace Ui {
class PlayerSelector;
}

class PlayerSelector : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerSelector(QWidget *parent = 0);
    ~PlayerSelector();

signals:
    void sendID(QString);

private slots:
    void on_searchPlayer_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PlayerSelector *ui;
    int IDIndex;
};

#endif // PLAYERSELECTOR_H
