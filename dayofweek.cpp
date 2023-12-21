#include "dayofweek.h"
#include "ui_dayofweek.h"

DayofWeek::DayofWeek(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DayofWeek)
{
    ui->setupUi(this);
    setWindowTitle("calendar. Поиск дня недели");
}

DayofWeek::~DayofWeek()
{
    delete ui;
}
bool DayofWeek::checkInput(int day, int month, int year){
    if (day == 0 || month == 0 || year == 0) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Пожалуйста, заполните поля корректно.");
        return false;
    }
    else if (year <= 1598 || year > 4092) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Год долже быть в промежутке от 1598 до 4092.");
        return false;
    }
    else if (month<=0 || month>12) { // Проверка на правильность ввода month
        QMessageBox::warning(this, "Некорректный ввод", "Номер месяца должен быть от 1 до 12.");
        return false;
    }
    // Проверка на правильность ввода day
    if (day < 1 || day > numberOfDays(month, year)) {
        QMessageBox::warning(this, "Некорректный ввод", "Нет такого дня в месяце");
        return false;
    }
    else {
        return true;
    }
}
void DayofWeek::on_back_clicked()
{
    this->close();
    MainWindow* main = static_cast<MainWindow*>(parent());
    main->show();
}


void DayofWeek::on_calculateDay_clicked()
{
    int year, month, day;
    year = ui->year->text().toInt();
    month = ui->month->text().toInt();
    day = ui->day->text().toInt();
    if (checkInput(day, month, year)){
    int result = dayNumber(day, month, year);
        QString days[7] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
        QMessageBox::about(this, "День недели", days[result]);
    }
}

