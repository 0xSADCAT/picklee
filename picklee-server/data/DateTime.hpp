#pragma once

#include <string>


/// Месяц
enum class Month
{
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
  Time(int hours, int minutes, int seconds) noexcept;

  static Time current() noexcept;

  int hours() const noexcept;
  void setHours(int newHours) noexcept;

  int minutes() const noexcept;
  void setMinutes(int newMinutes) noexcept;

  int seconds() const noexcept;
  void setSeconds(int newSeconds) noexcept;

  bool isValid() const noexcept;

  std::wstring toString() const noexcept;

  friend bool operator==(const Time& left, const Time& right) noexcept;
  friend bool operator!=(const Time& left, const Time& right) noexcept;
  friend bool operator<(const Time& left, const Time& right) noexcept;

private:
  int _hours;
  int _minutes;
  int _seconds;

  bool _valid;

  void validate();
};

bool operator==(const Time& left, const Time& right) noexcept;
bool operator!=(const Time& left, const Time& right) noexcept;
bool operator<(const Time& left, const Time& right) noexcept;


/// Дата
class Date
{
public:
  Date(int day, Month month, int year) noexcept;

  static Date current() noexcept;

  int day() const noexcept;
  void setDay(int newDay) noexcept;

  Month month() const noexcept;
  void setMonth(Month newMonth) noexcept;

  int year() const noexcept;
  void setYear(int newYear) noexcept;

  bool isValid() const noexcept;

  std::wstring toString(wchar_t sep = L'-') const noexcept;

  friend bool operator==(const Date& left, const Date& right) noexcept;
  friend bool operator!=(const Date& left, const Date& right) noexcept;
  friend bool operator<(const Date& left, const Date& right) noexcept;

private:
  int _day;
  Month _month;
  int _year;

  bool _valid;

  void validate();
};

bool operator==(const Date& left, const Date& right) noexcept;
bool operator!=(const Date& left, const Date& right) noexcept;
bool operator<(const Date& left, const Date& right) noexcept;


/// Дата и время
class DateTime
{
public:
  DateTime(const Time time, const Date date) noexcept;

  static DateTime current() noexcept;

  int hours() const noexcept;
  void setHours(int newHours) noexcept;

  int minutes() const noexcept;
  void setMinutes(int newMinutes) noexcept;

  int seconds() const noexcept;
  void setSeconds(int newSeconds) noexcept;

  int day() const noexcept;
  void setDay(int newDay) noexcept;

  Month month() const noexcept;
  void setMonth(Month newMonth) noexcept;

  int year() const noexcept;
  void setYear(int newYear) noexcept;

  const Time& time() const noexcept;
  void setTime(const Time& newTime) noexcept;

  const Date& date() const noexcept;
  void setDate(const Date& newDate) noexcept;

  bool isValid() const noexcept;

  std::wstring toString(wchar_t sep = L' ', wchar_t dateSep = L'-') const noexcept;

  friend bool operator==(const DateTime& left, const DateTime& right) noexcept;
  friend bool operator!=(const DateTime& left, const DateTime& right) noexcept;
  friend bool operator<(const DateTime& left, const DateTime& right) noexcept;

private:
  Time _time;
  Date _date;
};

bool operator==(const DateTime& left, const DateTime& right) noexcept;
bool operator!=(const DateTime& left, const DateTime& right) noexcept;
bool operator<(const DateTime& left, const DateTime& right) noexcept;
