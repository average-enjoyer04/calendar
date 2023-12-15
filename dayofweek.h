#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
#include "calcul.h"
namespace Ui {
class DayofWeek;
}

class DayofWeek : public QDialog
{
    Q_OBJECT

public:
    explicit DayofWeek(QWidget *parent = nullptr);
    ~DayofWeek();

private slots:
    void on_back_clicked();

    void on_calculateDay_clicked();

private:
    Ui::DayofWeek *ui;
    bool checkInput(int day, int month, int year);
};

#endif // DAYOFWEEK_H
