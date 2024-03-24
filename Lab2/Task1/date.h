#ifndef DATE_H
#define DATE_H

#include <QDate>

class Date {
private:
    int day;
    int month;
    int year;

    int NumOfDays[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
    Date(int, int, int);
    Date();

    Date NextDate();
    Date PreviousDate();
    bool IsLeap();
    short WeekNumber();
    int DaysTillYourBithday(Date bithdaydate);
    int Duration(Date date);

    bool isDateCorrect();
    int DaysInThisYear();
    Date getTodaysDate();
    int DateToDays();

};

Date StringToDate(QString);

#endif // DATE_H
