#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    if(Settings::load()->value("DBHost").isValid())
        ui->hostAddr->setText(Settings::load()->value("DBHost").toString());

    if(Settings::load()->value("DBName").isValid())
        ui->DBName->setText(Settings::load()->value("DBName").toString());

    if(Settings::load()->value("DBUser").isValid())
        ui->username->setText(Settings::load()->value("DBUser").toString());

    if(Settings::load()->value("DBPassword").isValid())
        ui->password->setText(Settings::load()->value("DBPassword").toString());

    if(Settings::load()->value("nightmode").isValid())
        if(Settings::load()->value("nightmode") == "true")
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

    Settings::save("DBHost",host);
    Settings::save("DBName",name);
    Settings::save("DBUser",user);
    Settings::save("DBPassword",password);
    Settings::save("changed","true");

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
        Settings::save("nightmode","true");
    else
        Settings::save("nightmode","false");

    delete this;
}
void Settings::save(QString key, QString value)
{
    QSettings settings("settings.ini",  QSettings::IniFormat);
    settings.setValue(key,value);

}

QSettings* Settings::load()
{
    QSettings* settings = new QSettings("settings.ini",  QSettings::IniFormat);
    return settings;
}
