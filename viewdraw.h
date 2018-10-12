#ifndef VIEWDRAW_H
#define VIEWDRAW_H

#include <QDialog>

#include <qDebug>

namespace Ui {
class ViewDraw;
}

class ViewDraw : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDraw(QWidget *parent = 0);
    ~ViewDraw();

private:
    Ui::ViewDraw *ui;
};

#endif // VIEWDRAW_H
