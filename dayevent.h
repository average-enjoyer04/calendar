#ifndef DAYEVENT_H
#define DAYEVENT_H

#include <QDialog>
#include "mainwindow.h"
#include "databasework.h"
#include "calcul.h"
namespace Ui {
class DayEvent;
}

class DayEvent : public QDialog
{
    Q_OBJECT

public:
    explicit DayEvent(DatabaseWork* dbData, QWidget *parent = nullptr);
    ~DayEvent();

private slots:
    void on_back_clicked();

    void on_addEvent_clicked();

    void on_delEvent_clicked();

    void on_checkDay_clicked();

private:
    Ui::DayEvent *ui;
    DatabaseWork* dbData;
    bool checkInput(int day, int month, QString& event);
};

#endif // DAYEVENT_H
