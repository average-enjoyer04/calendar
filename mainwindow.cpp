#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DatabaseWork* dbData, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("calendar. Главное меню");
    this->dbData = dbData;
}

MainWindow::~MainWindow()
{
    delete window;
    delete ui;
}

void MainWindow::on_dayofWeek_clicked()
{
    if (window != nullptr){
        delete window;  // Удаление существующего объекта
    }
    //hide();
    window = new DayofWeek(this);
    window->show();
}


void MainWindow::on_dayEvent_clicked()
{
    if (window != nullptr){
        delete window;  // Удаление существующего объекта
    }
    //hide();
    window = new DayEvent(dbData, this);
    window->show();
}


void MainWindow::on_calMonth_clicked()
{
    if (window != nullptr){
        delete window;  // Удаление существующего объекта
    }
    //hide();
    window = new MonthCal(dbData, this);
    window->show();
}


void MainWindow::on_calYear_clicked()
{
    if (window != nullptr){
        delete window;  // Удаление существующего объекта
    }
    //hide();
    window = new YearCal(dbData, this);
    window->show();
}


void MainWindow::on_exit_clicked()
{
    this->close();
    Authorization* main = static_cast<Authorization*>(parent());
    delete this;
    main->show();
}


void MainWindow::on_caldat_clicked()
{
    if (window != nullptr){
        delete window;  // Удаление существующего объекта
    }
    //hide();
    window = new CalDat(this);
    window->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Authorization* main = static_cast<Authorization*>(parent());
    QWidget::closeEvent(event);
    main->show();
}

