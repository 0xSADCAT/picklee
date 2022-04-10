#pragma once

#include <string>


/// Месяц
enum class Month {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};


/// Время
class Time
{
public:
    Time(int hours, int minutes, int seconds);

    static Time current();

    int hours() const;
    void setHours(int newHours);

    int minutes() const;
    void setMinutes(int newMinutes);

    int seconds() const;
    void setSeconds(int newSeconds);

    bool isValid() const;

    friend bool operator==(const Time& left, const Time& right);
    friend bool operator!=(const Time& left, const Time& right);
    friend bool operator<(const Time& left, const Time& right);

private:
    int _hours;
    int _minutes;
    int _seconds;

    bool _valid;

    void validate();
};

bool operator==(const Time& left, const Time& right);
bool operator!=(const Time& left, const Time& right);
bool operator<(const Time& left, const Time& right);


/// Дата
class Date
{
public:
    Date(int day, Month month, int year);

    static Date current();

    int day() const;
    void setDay(int newDay);

    Month month() const;
    void setMonth(Month newMonth);

    int year() const;
    void setYear(int newYear);

    bool isValid() const;

    friend bool operator==(const Date& left, const Date& right);
    friend bool operator!=(const Date& left, const Date& right);
    friend bool operator<(const Date& left, const Date& right);

private:
    int _day;
    Month _month;
    int _year;

    bool _valid;

    void validate();
};

bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);
bool operator<(const Date& left, const Date& right);


/// Дата и время
class DateTime
{
public:
    DateTime(const Time time, const Date date);

    static DateTime current();

    int hours() const;
    void setHours(int newHours);

    int minutes() const;
    void setMinutes(int newMinutes);

    int seconds() const;
    void setSeconds(int newSeconds);

    int day() const;
    void setDay(int newDay);

    Month month() const;
    void setMonth(Month newMonth);

    int year() const;
    void setYear(int newYear);

    const Time& time() const;
    void setTime(const Time& newTime);

    const Date& date() const;
    void setDate(const Date& newDate);

    bool isValid() const;

    friend bool operator==(const DateTime& left, const DateTime& right);
    friend bool operator!=(const DateTime& left, const DateTime& right);
    friend bool operator<(const DateTime& left, const DateTime& right);

private:
    Time _time;
    Date _date;
};

bool operator==(const DateTime& left, const DateTime& right);
bool operator!=(const DateTime& left, const DateTime& right);
bool operator<(const DateTime& left, const DateTime& right);
