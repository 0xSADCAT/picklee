#include "DateTime.hpp"

#include <chrono>


Time::Time(int hours, int minutes, int seconds)
    : _hours(hours),
      _minutes(minutes),
      _seconds(seconds),
      _valid(false)
{
    validate();
}


Time Time::current()
{
}


int Time::hours() const
{
    return _hours;
}


void Time::setHours(int newHours)
{
    _hours = newHours;
    validate();
}


int Time::minutes() const
{
    return _minutes;
}


void Time::setMinutes(int newMinutes)
{
    _minutes = newMinutes;
    validate();
}


int Time::seconds() const
{
    return _seconds;
}


void Time::setSeconds(int newSeconds)
{
    _seconds = newSeconds;
    validate();
}


bool Time::isValid() const
{
    return _valid;
}


void Time::validate()
{
    _valid = (_hours >= 0 and _hours < 24) and (_minutes >= 0 and _minutes < 60) and (_seconds >= 0 and _seconds < 60);
}


Date::Date(int day, Month month, int year)
    : _day(day),
      _month(month),
      _year(year),
      _valid(false)
{
    validate();
}


Date Date::current()
{
}


int Date::day() const
{
    return _day;
}


void Date::setDay(int newDay)
{
    _day = newDay;
    validate();
}


Month Date::month() const
{
    return _month;
}


void Date::setMonth(Month newMonth)
{
    _month = newMonth;
    validate();
}


int Date::year() const
{
    return _year;
}


void Date::setYear(int newYear)
{
    _year = newYear;
    validate();
}


bool Date::isValid() const
{
    return _valid;
}


void Date::validate()
{
}


DateTime::DateTime(const Time time, const Date date)
    : Time(time),
      Date(date)
{
}

DateTime DateTime::current()
{
    return DateTime(Time::current(), Date::current());
}


bool DateTime::isValid() const
{
    return Time::isValid() and Date::isValid();
}
