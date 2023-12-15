#include "yearcal.h"
#include "ui_yearcal.h"

YearCal::YearCal(DatabaseWork* dbData, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::YearCal)
{
    ui->setupUi(this);
    this->dbData = dbData;
    ui->month->setPlaceholderText("Введите номер месяца");
}

YearCal::~YearCal()
{
    delete widget;
    delete ui;
}

void YearCal::on_back_clicked()
{
    this->close();
    MainWindow* main = static_cast<MainWindow*>(parent());
    //delete this;
    delete widget;
    widget = nullptr;
    main->show();
}
QString YearCal::daysColor(int month, std::set<int>& dates){
    int days;
    int dayNum = dayNumber(1, month+1, year);;
    days = numberOfDays(month+1, year);
    if (dayNum==0){
        dayNum=7;
    }
    dayNum-=1;
    QString monthName = getMonthName(month+1);
    int padding = (35 - monthName.length()) / 2;
    QString centeredMonthName = QString("%1%2%3").arg(" ", padding, ' ').arg(monthName).arg(" ", padding, ' ');
    QString text = "<pre><font size=\"3\">";
    text += "<strong>" + centeredMonthName + "</strong>";
    text += "<font color=\"blue\">\n   Пн   Вт   Ср   Чт   Пт   Сб   Вс\n</font>";
    int k;
    for (k = 0; k < dayNum; k++)
    {
        text += "     "; // Добавляем отступы к строке
    }

    for (int j = 1; j <= days; j++)
    {
        if (dates.count(j)) {
            text += QString("<font color=\"green\"><strong><b>%1</b><strong></font>").arg(j, 5);
        }
        else if (k == 5 || k == 6)
        {
            text += QString("<font color=\"red\">%1</font>").arg(j, 5);
        }
        else {
            text += QString("%1").arg(j, 5); // Добавляем число к строке с отступом
        }
        if (++k > 6)
        {
            k = 0;
            text += "\n"; // Добавляем переход на новую строку
        }

    }
    text += "<\font>";
    return text;
}
QString YearCal::daysinMonth(int month){
    int days;
    int dayNum = dayNumber(1, month+1, year);;
    days = numberOfDays(month+1, year);
    if (dayNum==0){
        dayNum=7;
    }
    dayNum-=1;
    QString monthName = getMonthName(month+1);
    int padding = (34 - monthName.length()) / 2;
    QString centeredMonthName = QString("%1%2%3").arg(" ", padding, ' ').arg(monthName).arg(" ", padding, ' ');
    QString text = "<pre><font size=\"3\">";
    text += "<strong>" + centeredMonthName + "</strong>";
    text += "<font color=\"blue\">\n   Пн   Вт   Ср   Чт   Пт   Сб   Вс\n</font>";
    int k;
    for (k = 0; k < dayNum; k++)
    {
        text += "     "; // Добавляем отступы к строке
    }

    for (int j = 1; j <= days; j++)
    {
        if (k == 5 || k == 6)
        {
            text += QString("<font color=\"red\">%1</font>").arg(j, 5);
        }
        else {
            text += QString("%1").arg(j, 5); // Добавляем число к строке с отступом
        }
        if (++k > 6)
        {
            k = 0;
            text += "\n"; // Добавляем переход на новую строку
        }

    }
    text += "<\font>";
    return text;
}
void YearCal::on_calOut_clicked()
{
    if (widget != nullptr){
        delete widget;  // Удаление существующего объекта dbData
    }
    year = ui->year->text().toInt();
    if (year > 1598 && year < 4092) {
        widget = new QWidget;
        widget->setWindowTitle(QString("Календарь на %1 год").arg(year));
        int n;
        if (ui->checkBox4->isChecked()) {
            widget->setMinimumWidth(1150);
            widget->setMinimumHeight(450);
            n = 4;
        }
        else if (ui->checkBox6->isChecked()) {
            widget->setMinimumWidth(1700);
            widget->setMinimumHeight(275);
            n = 6;
        }
        else {
            widget->setMinimumWidth(850);
            widget->setMinimumHeight(550);
            n = 3;
        }
        QGridLayout *layout = new QGridLayout(widget);
        QString text;
        int j = 0, k = 0;
        if (!ui->checkBox->isChecked()){
        for (int i = 0; i < 12; i++){
            text = daysinMonth(i);
            QLabel *label =  new QLabel(text);
            layout->addWidget(label,k,j);
            j++;
            if (j == n){
                k++;
                j = 0;
            }
        }}
        else {
            for (int i = 0; i < 12; i++){
                if (!(dbData->datesArray[i].empty())) {
                    text = daysColor(i, dbData->datesArray[i]);
                }
                else {
                    text = daysinMonth(i);
                }
                QLabel *label =  new QLabel(text);
                layout->addWidget(label,k,j);
                j++;
                if (j == n){
                    k++;
                    j = 0;
                }
            }
        }

        widget->show();
    }
    else {
        QMessageBox::warning(this, "Некорректный ввод", "Год долже быть в промежутке от 1598 до 4092.");
    }
}
bool YearCal::checkInput(int day, int month){
    if (month == 0 || day == 0) { // Проверка на пустые поля
        QMessageBox::warning(this, "Некорректный ввод", "Пожалуйста, заполните поля корректно.");
        return false;
    }
    else if (month<=0 || month>12) { // Проверка на правильность ввода month
        QMessageBox::warning(this, "Некорректный ввод", "Номер месяца должен быть от 1 до 12.");
        return false;
    }
    else if (day < 1 || day > numberOfDays(month, 2020)) {
        QMessageBox::warning(this, "Некорректный ввод", "Нет такого дня в месяце");
        return false;
    }
    else {
        return true;
    }
}
void YearCal::on_checkEvent_clicked()
{
    int day = ui->day->text().toInt();
    int month = ui->month->text().toInt();
    if (checkInput(day, month)){
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

