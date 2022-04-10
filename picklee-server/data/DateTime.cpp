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
    _valid = false;

    if (_day <= 0) {
        _valid = false;
        return;
    }

    int max_days;
    if (_month == Month::April or _month == Month::June or _month == Month::September or _month == Month::November) {
        max_days = 30;
    } else {
        if (_month == Month::February) {
            max_days = __isleap(_year) ? 29 : 28;
        } else {
            max_days = 31;
        }
    }

    if (_day > max_days) {
        _valid = false;
        return;
    }

    if (_year <= 0) {
        _valid = false;
        return;
    }

    _valid = true;
}


DateTime::DateTime(const Time time, const Date date)
    : _time(time),
      _date(date)
{
}

DateTime DateTime::current()
{
    return DateTime(Time::current(), Date::current());
}


int DateTime::hours() const
{
    return _time.hours();
}


void DateTime::setHours(int newHours)
{
    _time.setHours(newHours);
}


int DateTime::minutes() const
{
    return _time.minutes();
}


void DateTime::setMinutes(int newMinutes)
{
    _time.setMinutes(newMinutes);
}


int DateTime::seconds() const
{
    return _time.seconds();
}


void DateTime::setSeconds(int newSeconds)
{
    _time.setSeconds(newSeconds);
}


int DateTime::day() const
{
    return _date.day();
}


void DateTime::setDay(int newDay)
{
    _date.setDay(newDay);
}


Month DateTime::month() const
{
    return _date.month();
}


void DateTime::setMonth(Month newMonth)
{
    _date.setMonth(newMonth);
}


int DateTime::year() const
{
    return _date.year();
}


void DateTime::setYear(int newYear)
{
    _date.setYear(newYear);
}


bool DateTime::isValid() const
{
    return _time.isValid() and _date.isValid();
}


const Time& DateTime::time() const
{
    return _time;
}


void DateTime::setTime(const Time& newTime)
{
    _time = newTime;
}


const Date& DateTime::date() const
{
    return _date;
}


void DateTime::setDate(const Date& newDate)
{
    _date = newDate;
}


bool operator==(const Time& left, const Time& right)
{
    return left._hours == right._hours and left._minutes == right._minutes and left._seconds == right._seconds;
}


bool operator!=(const Time& left, const Time& right)
{
    return left._hours != right._hours or left._minutes != right._minutes or left._seconds != right._seconds;
}


bool operator<(const Time& left, const Time& right)
{
    if (left._hours < right._hours) {
        return true;
    }

    if (left._hours == right._hours) {
        if (left._minutes < right._minutes) {
            return true;
        } else if (left._minutes == right._minutes) {
            return left._seconds < right._seconds;
        }
    }

    return false;
}


bool operator==(const Date& left, const Date& right)
{
    return left._day == right._day and left._month == right._month and left._year == right._year;
}


bool operator!=(const Date& left, const Date& right)
{
    return left._day != right._day or left._month != right._month or left._year != right._year;
}


bool operator<(const Date& left, const Date& right)
{
    if (left._year < right._year) {
        return true;
    } else if (left._year == right._year) {
        if (static_cast<int>(left._month) < static_cast<int>(right._month)) {
            return true;
        } else if (static_cast<int>(left._month) == static_cast<int>(right._month)) {
            return left._day < right._day;
        }
    }
    return false;
}


bool operator==(const DateTime& left, const DateTime& right)
{
    return left._date == right._date and left._time == right._time;
}


bool operator!=(const DateTime& left, const DateTime& right)
{
    return left._date != right._date or left._time != right._time;
}


bool operator<(const DateTime& left, const DateTime& right)
{
    if (left._date < right._date) {
        return true;
    } else if (left._date == right._date) {
        return left._time < right._time;
    }

    return false;
}
