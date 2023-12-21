#ifndef CALYEAR_H
#define CALYEAR_H

#include <QMainWindow>
#include <QGridLayout>
#include <set>
#include "mainwindow.h"
#include "databasework.h"
#include "calcul.h"

namespace Ui {
class CalYear;
}

class CalYear : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalYear(DatabaseWork* dbData, QWidget *parent = nullptr);
    ~CalYear();
private slots:
    void on_back_clicked();

    void on_calOut_clicked();

    void on_checkEvent_clicked();
private:
    Ui::CalYear *ui;
    DatabaseWork* dbData;
    QString daysinMonth(int month);
    QString daysColor(int month, std::set<int>& dates);
    bool checkInput(int month, int year);
    int year;
    QWidget* widget = nullptr;
};

#endif // CALYEAR_H
