#pragma once

#include <string>


/// Месяц
enum class Month {
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};


/// Время
class Time
{
public:
    Time(int hours, int minutes, int seconds);

    virtual ~Time() = default;

    static Time current();

    int hours() const;
    void setHours(int newHours);

    int minutes() const;
    void setMinutes(int newMinutes);

    int seconds() const;
    void setSeconds(int newSeconds);

    virtual bool isValid() const;

private:
    int _hours;
    int _minutes;
    int _seconds;

    bool _valid;

    void validate();
};


/// Дата
class Date
{
public:
    Date(int day, Month month, int year);

    virtual ~Date() = default;

    static Date current();

    int day() const;
    void setDay(int newDay);

    Month month() const;
    void setMonth(Month newMonth);

    int year() const;
    void setYear(int newYear);

    virtual bool isValid() const;

private:
    int _day;
    Month _month;
    int _year;

    bool _valid;

    void validate();
};


/// Дата и время
class DateTime : public Time,
                 public Date
{
public:
    DateTime(const Time time, const Date date);

    static DateTime current();

    virtual bool isValid() const override;
};

