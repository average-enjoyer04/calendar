#include "monthcal.h"
#include "ui_monthcal.h"

MonthCal::MonthCal(DatabaseWork* dbData, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MonthCal)
{
    ui->setupUi(this);
    this->dbData = dbData;
    ui->month->setPlaceholderText("Введите номер месяца");
}

MonthCal::~MonthCal()
{
    delete ui;
}
bool MonthCal::checkInput(int month, int year){
    if (month == 0 || year == 0) { // Проверка на пустые поля
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
    else {
        return true;
    }
}
void MonthCal::on_back_clicked()//если пользователь хочет выйти
{
    this->close();
    MainWindow* main = static_cast<MainWindow*>(parent());
    main->show();
}
void MonthCal::fillTableColor(int startDayOfWeek, int numOfDays, std::set<int>& dates)//если есть особые дни
{
    int row = 1; // Изменяем начальную строку на 1, чтобы числа месяца не попадали в строку названий дней недели
    int col = startDayOfWeek;

    for (int i = 1; i <= numOfDays; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        if (col == 5 || col == 6) { // Если текущий день недели - выходной
            item->setForeground(QColor(Qt::red)); // Установить красный цвет шрифта
        }
        if (dates.count(i)) {
            // Если совпадение, окрашиваем клеточку в желтый цвет
            item->setBackground(Qt::yellow);
        }
        ui->tableWidget->setItem(row, col, item);

        ++col;
        if (col > 6) {
            col = 0;
            ++row;
        }
    }
}
void MonthCal::fillTableMonth(int startDayOfWeek, int numOfDays)// заполняем таблицу
{
    int row = 1; // Изменяем начальную строку на 1, чтобы числа месяца не попадали в строку названий дней недели
    int col = startDayOfWeek;

    for (int i = 1; i <= numOfDays; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        if (col == 5 || col == 6) { // Если текущий день недели - выходной
            item->setForeground(QColor(Qt::red)); // Установить красный цвет шрифта
        }
        ui->tableWidget->setItem(row, col, item);
        ++col;
        if (col > 6) {
            col = 0;
            ++row;
        }
    }
}

void MonthCal::on_tableWidget_cellDoubleClicked(int row, int column) // пользователь решил узнать про этот день
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // отключает возможность редактирования ячеек
    std::map<int, std::string> dates = {{ 15, "Особый день" }, { 17, "День дня" }, { 27, "День дерева" }};
    if (isTableDisplayed) // если есть таблица на экране
    {
        QTableWidgetItem* item = ui->tableWidget->item(row, column);
        if (item != nullptr) {
            QString selectedValue = item->text();
            bool isMonthName = (selectedValue.length() > 3); // если это день недели
            if (!isMonthName) {
                //QString selectedValue = ui->tableWidget->item(row, column)->text();
                if (dbData->datesArray[month-1].count(selectedValue.toInt())) {
                    QMessageBox::about(this, "В этот день", dbData->getEventData(selectedValue.toInt(), month));
                }
                else {
                    QMessageBox::about(this, "В этот день", "На эту дату ничего не запланировано");
                }
            }
        }

    }
}


void MonthCal::on_choose_clicked()
{
    ui->tableWidget->clear();
    int year;
    year = ui->year->text().toInt();//
    month = ui->month->text().toInt();
    qDebug()<<month;
    qDebug()<<year;
    if (checkInput(month, year)) {
        int dayNum;
        int days;
        QString nameMonth = getMonthName(month);
        ui->monthName->setText(nameMonth);
        ui->tableWidget->setRowCount(7); // количество строк
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->verticalHeader()->setVisible(false); // Убрать номера строк сбоку
        QStringList daysOfWeek = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
        ui->tableWidget->setHorizontalHeaderLabels(daysOfWeek);
        ui->tableWidget->horizontalHeader()->setStyleSheet("background-color: lightblue;");
        dayNum = dayNumber(1, month, year);
        days = numberOfDays(month, year);
        if (dayNum==0){
            dayNum=7;
        }
        dayNum-=1;
        if (ui->checkBox->isChecked()) {
            if (!(dbData->datesArray[month-1].empty())) {
                fillTableColor(dayNum, days, dbData->datesArray[month-1]);
            }
            else {
                fillTableMonth(dayNum, days);
            }
        }
        else {
            fillTableMonth(dayNum, days);
        }
        isTableDisplayed = true;
    }
}

