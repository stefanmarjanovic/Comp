#ifndef VIEWDRAW_H
#define VIEWDRAW_H

#include <QDialog>

#include <qDebug>
#include "database.h"

namespace Ui {
class ViewDraw;
}

class ViewDraw : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDraw(QString id, QWidget *parent = 0);
    ~ViewDraw();

private slots:
    void on_buttonPDFExport_clicked();

    void on_buttonOK_clicked();

private:
    Ui::ViewDraw *ui;
    QString id;
    QString htmlOut;
};

#endif // VIEWDRAW_H
