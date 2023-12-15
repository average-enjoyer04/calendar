#ifndef MONTHCAL_H
#define MONTHCAL_H

#include <QMainWindow>
#include <QTableWidget>
#include <QColor>
#include <set>
#include <QMessageBox>
#include "mainwindow.h"
#include "databasework.h"
#include "calcul.h"
namespace Ui {
class MonthCal;
}

class MonthCal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MonthCal(DatabaseWork* dbData, QWidget *parent = nullptr);
    ~MonthCal();

private slots:
    void on_back_clicked();

    void on_choose_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MonthCal *ui;
    DatabaseWork* dbData;
    void fillTableMonth(int startDayOfWeek, int numOfDays);
    void fillTableColor(int startDayOfWeek, int numOfDays, std::set<int>& dates);
    bool checkInput(int month, int year);
    bool isTableDisplayed;
    int month;
};

#endif // MONTHCAL_H
