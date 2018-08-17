#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "refine.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Refine_clicked();

private:
    Ui::MainWindow *ui;
    Refine *refine;
};

#endif // MAINWINDOW_H
