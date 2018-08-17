#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Refine_clicked()
{
    refine = new Refine(this);
    refine->show();
}
