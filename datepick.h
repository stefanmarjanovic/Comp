#ifndef DATEPICK_H
#define DATEPICK_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class DatePick;
}

class DatePick : public QWidget
{
    Q_OBJECT

public:
    explicit DatePick(QWidget *parent = 0);
    ~DatePick();

private slots:
    void on_calendarWidget_selectionChanged();

signals:
    void sendDate(const QString);

private:
    Ui::DatePick *ui;
};

#endif // DATEPICK_H
