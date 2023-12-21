#include "caldat.h"
#include "ui_caldat.h"

CalDat::CalDat(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CalDat)
{
    ui->setupUi(this);
    setWindowTitle("calendar. Калькулятор дат");
}

CalDat::~CalDat()
{
    delete ui;
}

void CalDat::on_difButton_clicked()
{
    QDate date1 = ui->firstDate->date();
    QDate date2 = ui->secondDate->date();
    // Вычисление новой даты
    qint64 newDate = date1.daysTo(date2);
    QString text = QString::number(newDate);
    // Отображение результата
    ui->difDays->setText(text);
}


void CalDat::on_sumDays_clicked()
{
    int days = ui->numDays->text().toInt();
    QDate date = ui->defaDate->date();
    if (days == 0 || days > 10000 ) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Количество дней должно быть в интервале от 1 до 10000");
    }
    else {
    // Вычисление новой даты
    QDate newDate = date.addDays(days);

    // Отображение результата
    ui->sumDayslab->setText(newDate.toString("dd.MM.yyyy"));
    }
}



void CalDat::on_checkYear_clicked()
{
    int year = ui->year->text().toInt();
    if (year >= 1400 && year <= 9999) { // Проверка на корректный диапазон года
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            QMessageBox::about(this, "Проверка года", "Год високосный");
        else
            QMessageBox::about(this, "Проверка года", "Год невисокосный");

    }
    else {
        QMessageBox::warning(this, "Некорректный ввод", "Год должен быть в интервале от 1400 до 9999");
    }
    ui->year->clear();
}

