#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    if(dbSettings.value("DBHost").isValid())
        ui->hostAddr->setText(dbSettings.value("DBHost").toString());

    if(dbSettings.value("DBName").isValid())
        ui->DBName->setText(dbSettings.value("DBName").toString());

    if(dbSettings.value("DBUser").isValid())
        ui->username->setText(dbSettings.value("DBUser").toString());

    if(dbSettings.value("DBPassword").isValid())
        ui->password->setText(dbSettings.value("DBPassword").toString());
}

Settings::~Settings()
{

    Database::dbOpen();
    emit sendRefresh("ALL");
    delete ui;
}

void Settings::on_apply_clicked()
{

    dbSettings.setValue("DBHost",host);
    dbSettings.setValue("DBName",name);
    dbSettings.setValue("DBUser",user);
    dbSettings.setValue("DBPassword",password);
    dbSettings.setValue("changed","true");

    Settings::~Settings();
}

void Settings::on_test_clicked()
{
    host=ui->hostAddr->text();
    name=ui->DBName->text();
    user=ui->username->text();
    password=ui->password->text();
    if(Database::test(host,name,user,password))
        ui->apply->setEnabled(true);
    else
        ui->apply->setEnabled(false);
}

void Settings::on_cancel_clicked()
{
    Settings::~Settings();
}
void Settings::reject()
{
    Settings::~Settings();
}
