#include "dayevent.h"
#include "ui_dayevent.h"

DayEvent::DayEvent(DatabaseWork* dbData, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DayEvent)
{
    ui->setupUi(this);
    setWindowTitle("calendar. Особые дни");
    this->dbData = dbData;
}

DayEvent::~DayEvent()
{
    delete ui;
}

bool DayEvent::checkInput(int day, int month, QString& event){
    if (day == 0 || month == 0 || event.isEmpty()) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Пожалуйста, заполните поля корректно.");
        return false;
    }
    else if (month<=0 || month>12) { // Проверка на правильность ввода month
        QMessageBox::warning(this, "Некорректный ввод", "Номер месяца должен быть в промежутке от 1 до 12.");
        return false;
    }
    // Проверка на правильность ввода day
    if (day < 1 || day > numberOfDays(month, 2020)) {
        QMessageBox::warning(this, "Некорректный ввод", "Нет такого дня в месяце");
        return false;
    }
    else {
        return true;
    }
}

void DayEvent::on_back_clicked()
{
    this->close();
    MainWindow* main = static_cast<MainWindow*>(parent());
    main->show();
}

void DayEvent::on_addEvent_clicked()
{
    int day = ui->day->text().toInt();
    int month = ui->month->text().toInt();
    QString event = ui->event->text();
    if (checkInput(day, month, event)){
        // Проверка на наличие уже существующего события для данной даты
        if (dbData->datesArray[month - 1].count(day) > 0) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Подтвердите замену", "Событие уже существует для выбранной даты. Вы хотите заменить его?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                dbData->updateSpecDatData(day, month, event);
            }
        }
        else {
            // Добавление/обновление данных в базе данных
            QString reply = dbData->addSpecDatData(day, month, event);
            QMessageBox::about(this, "Добавление события", reply);
        }
        ui->day->clear();
        ui->month->clear();
        ui->event->clear();
    }
}

void DayEvent::on_delEvent_clicked()
{
    int day = ui->day->text().toInt();
    int month = ui->month->text().toInt();
    QString event = "Default";
    if (checkInput(day, month, event)){
        // Проверка на наличие уже существующего события для данной даты
        if (dbData->datesArray[month - 1].count(day) > 0) {
            QString reply = dbData->deleteSpecDatData(day, month);
            QMessageBox::about(this, "Удаление события", reply);
        }
        else {
            QMessageBox::about(this, "Удаление события", "На эту дату ничего не запланировано");
        }
        ui->day->clear();
        ui->month->clear();
    }
}


void DayEvent::on_checkDay_clicked()
{
    int day = ui->day->text().toInt();
    int month = ui->month->text().toInt();
    QString event = "Default";
    if (checkInput(day, month, event)){
        // Проверка на наличие уже существующего события для данной даты
        if (dbData->datesArray[month - 1].count(day) > 0) {
            QString reply = dbData->getEventData(day, month);
            QMessageBox::about(this, "Проверка дня", reply);
        }
        else {
            QMessageBox::about(this, "Проверка дня", "На эту дату ничего не запланировано");
        }
        ui->day->clear();
        ui->month->clear();
    }
}

