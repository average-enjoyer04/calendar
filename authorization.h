#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>
#include "databasework.h"
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Authorization;
}
QT_END_NAMESPACE

class Authorization : public QMainWindow
{
    Q_OBJECT

public:
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

private slots:
    void on_authorization_clicked();

    void on_registration_clicked();

private:
    Ui::Authorization *ui;
    DatabaseWork* dbData = nullptr;
    void closeEvent(QCloseEvent *event);
    bool checkInput(QString& login, QString& password);
};
#endif // AUTHORIZATION_H
