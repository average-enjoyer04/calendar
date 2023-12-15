#ifndef YEARCAL_H
#define YEARCAL_H

#include <QDialog>
#include <set>
#include "mainwindow.h"
#include "databasework.h"
#include "calcul.h"
namespace Ui {
class YearCal;
}

class YearCal : public QDialog
{
    Q_OBJECT

public:
    explicit YearCal(DatabaseWork* dbData, QWidget *parent = nullptr);
    ~YearCal();

private slots:
    void on_back_clicked();

    void on_calOut_clicked();

    void on_checkEvent_clicked();

private:
    Ui::YearCal *ui;
    DatabaseWork* dbData;
    QString daysinMonth(int month);
    QString daysColor(int month, std::set<int>& dates);
    bool checkInput(int month, int year);
    int year;
    QWidget* widget = nullptr;
};

#endif // YEARCAL_H
