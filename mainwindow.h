#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasework.h"
#include "dayofweek.h"
#include "dayevent.h"
#include "monthcal.h"
#include "yearcal.h"
#include "caldat.h"
#include "authorization.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DatabaseWork* dbData, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dayofWeek_clicked();

    void on_dayEvent_clicked();

    void on_calMonth_clicked();

    void on_calYear_clicked();

    void on_exit_clicked();

    void on_caldat_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseWork* dbData;
    QWidget* window = nullptr;
};

#endif // MAINWINDOW_H
