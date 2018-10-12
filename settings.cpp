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

    if(dbSettings.value("nightmode").isValid())
       if(dbSettings.value("nightmode") == "true")
           ui->nightmode->setChecked(true);
       else
           ui->nightmode->setChecked(false);
}

Settings::~Settings()
{
    Database::dbOpen();
    emit sendRefresh("ALL");
    emit sendLoadStyleSheet();
    delete ui;
}

void Settings::on_apply_clicked()
{

    dbSettings.setValue("DBHost",host);
    dbSettings.setValue("DBName",name);
    dbSettings.setValue("DBUser",user);
    dbSettings.setValue("DBPassword",password);
    dbSettings.setValue("changed","true");

    delete this;
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
    delete this;
}
void Settings::reject()
{
    delete this;
}

void Settings::on_applyAppearance_clicked()
{
    if(ui->nightmode->isChecked())
        dbSettings.setValue("nightmode","true");
    else
        dbSettings.setValue("nightmode","false");

    delete this;
}
