#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

#include "database.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    static void save(QString key, QString value);
    static QSettings* load();
    ~Settings();

private slots:
    void on_apply_clicked();

    void on_test_clicked();

    void on_cancel_clicked();

    void on_applyAppearance_clicked();

signals:
    void sendRefresh(QString);
    void sendLoadStyleSheet();
private:
    Ui::Settings *ui;
    QString host, name, user, password;
    void reject();

};

#endif // SETTINGS_H
