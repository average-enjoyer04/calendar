#include "calcul.h"

int dayNumber(int day, int month, int year)
{
    static int t[] = { 28, 31, 2, 5, 7, 10, 12, 15, 18, 20, 23, 25 };
    year -= month < 3;
    int result = (year%100 + (year%100) / 4 - 2*(year / 100) + year / 400 + t[month - 1] + day)% 7;
    if (result < 0){
        result+=7;
    }
    return result;
}

QString getMonthName(int monthNumber)
{
    QString months[] = { "Январь", "Февраль", "Март",
        "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь",
        "Октябрь", "Ноябрь", "Декабрь"
    };
    return (months[monthNumber-1]);
}

int numberOfDays(int monthNumber, int year)
{
    monthNumber--;
    if (monthNumber == 0)
        return (31);

    else if (monthNumber == 1)
    {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }
    else if (monthNumber == 2)
        return (31);
    else if (monthNumber == 3)
        return (30);
    else if (monthNumber == 4)
        return (31);
    else if (monthNumber == 5)
        return (30);
    else if (monthNumber == 6)
        return (31);
    else if (monthNumber == 7)
        return (31);
    else if (monthNumber == 8)
        return (30);
    else if (monthNumber == 9)
        return (31);
    else if (monthNumber == 10)
        return (30);
    else if (monthNumber == 11)
        return (31);
}


