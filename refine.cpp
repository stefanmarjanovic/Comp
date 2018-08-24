#include "refine.h"
#include "ui_refine.h"
#include "mainwindow.h"

Refine::Refine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Refine)
{
    ui->setupUi(this);
}

Refine::~Refine()
{
    delete ui;
}
