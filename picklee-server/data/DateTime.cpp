#include "DateTime.hpp"

#include <cassert>
#include <chrono>
#include <ctime>
#include <ratio>
#include <tuple>


Time::Time(int hours, int minutes, int seconds) noexcept
    : _hours(hours), _minutes(minutes), _seconds(seconds), _valid(false)
{
  validate();
}


Time Time::current() noexcept
{
  using namespace std::chrono;

  /// Поправка на часовой пояс
  static constexpr auto hourDelta = 3h;

  auto time = system_clock::to_time_t(system_clock::now() + hourDelta);
  int seconds = time % 60;
  time /= 60;
  int minutes = time % 60;
  time /= 60;
  int hours = time % 24;

  return Time(hours, minutes, seconds);
}


int Time::hours() const noexcept
{
  return _hours;
}


void Time::setHours(int newHours) noexcept
{
  _hours = newHours;
  validate();
}


int Time::minutes() const noexcept
{
  return _minutes;
}


void Time::setMinutes(int newMinutes) noexcept
{
  _minutes = newMinutes;
  validate();
}


int Time::seconds() const noexcept
{
  return _seconds;
}


void Time::setSeconds(int newSeconds) noexcept
{
  _seconds = newSeconds;
  validate();
}


bool Time::isValid() const noexcept
{
  return _valid;
}


std::wstring Time::toString() const noexcept
{
  return std::to_wstring(_hours) + L':' + std::to_wstring(_minutes) + L':' + std::to_wstring(_seconds);
}


void Time::validate()
{
  _valid = (_hours >= 0 and _hours < 24) and (_minutes >= 0 and _minutes < 60) and (_seconds >= 0 and _seconds < 60);
}


Date::Date(int day, Month month, int year) noexcept : _day(day), _month(month), _year(year), _valid(false)
{
  validate();
}


namespace
{
/**
 * @brief Конвертирует время из std::chrono в структуру std::tm
 * @param tp Точка времени для конвертации
 * @return Структура std::tm
 *
 * @author Minsheng Liu
 * @link https://gist.github.com/notcome/526b1fbca6cb359c1152
 * Thanks a lot!
 */
std::tm toUTCTime(const std::chrono::system_clock::time_point& tp);
}


Date Date::current() noexcept
{
  using namespace std::chrono;

  /// Поправка, т.к. функция возвращает количество лет с 1900 года
  constexpr int deltaYear = 1900;

  std::tm tm = toUTCTime(system_clock::now());

  // Если сработает - функции в анонимном namespace что-то сделали не так
  assert(tm.tm_mday >= 1 and tm.tm_mday <= 31);
  assert(tm.tm_mon >= 0 and tm.tm_mon < 12);
  assert(tm.tm_year > 0);

  int day = tm.tm_mday;
  Month month = static_cast<Month>(tm.tm_mon + 1);
  int year = tm.tm_year + deltaYear;

  return Date(day, month, year);
}


int Date::day() const noexcept
{
  return _day;
}


void Date::setDay(int newDay) noexcept
{
  _day = newDay;
  validate();
}


Month Date::month() const noexcept
{
  return _month;
}


void Date::setMonth(Month newMonth) noexcept
{
  _month = newMonth;
  validate();
}


int Date::year() const noexcept
{
  return _year;
}


void Date::setYear(int newYear) noexcept
{
  _year = newYear;
  validate();
}


bool Date::isValid() const noexcept
{
  return _valid;
}


std::wstring Date::toString(wchar_t sep) const noexcept
{
  return std::to_wstring(_day) + sep + std::to_wstring(static_cast<int>(_month)) + sep + std::to_wstring(_year);
}


void Date::validate()
{
  _valid = false;

  if (_day <= 0)
  {
    _valid = false;
    return;
  }

  int max_days;
  if (_month == Month::April or _month == Month::June or _month == Month::September or _month == Month::November)
  {
    max_days = 30;
  }
  else
  {
    if (_month == Month::February)
    {
      max_days = __isleap(_year) ? 29 : 28;
    }
    else
    {
      max_days = 31;
    }
  }

  if (_day > max_days)
  {
    _valid = false;
    return;
  }

  if (_year <= 0)
  {
    _valid = false;
    return;
  }

  _valid = true;
}


DateTime::DateTime(const Time time, const Date date) noexcept : _time(time), _date(date)
{
}

DateTime DateTime::current() noexcept
{
  return DateTime(Time::current(), Date::current());
}


int DateTime::hours() const noexcept
{
  return _time.hours();
}


void DateTime::setHours(int newHours) noexcept
{
  _time.setHours(newHours);
}


int DateTime::minutes() const noexcept
{
  return _time.minutes();
}


void DateTime::setMinutes(int newMinutes) noexcept
{
  _time.setMinutes(newMinutes);
}


int DateTime::seconds() const noexcept
{
  return _time.seconds();
}


void DateTime::setSeconds(int newSeconds) noexcept
{
  _time.setSeconds(newSeconds);
}


int DateTime::day() const noexcept
{
  return _date.day();
}


void DateTime::setDay(int newDay) noexcept
{
  _date.setDay(newDay);
}


Month DateTime::month() const noexcept
{
  return _date.month();
}


void DateTime::setMonth(Month newMonth) noexcept
{
  _date.setMonth(newMonth);
}


int DateTime::year() const noexcept
{
  return _date.year();
}


void DateTime::setYear(int newYear) noexcept
{
  _date.setYear(newYear);
}


bool DateTime::isValid() const noexcept
{
  return _time.isValid() and _date.isValid();
}

std::wstring DateTime::toString(wchar_t sep, wchar_t dateSep) const noexcept
{
  return _date.toString(dateSep) + sep + _time.toString();
}


const Time& DateTime::time() const noexcept
{
  return _time;
}


void DateTime::setTime(const Time& newTime) noexcept
{
  _time = newTime;
}


const Date& DateTime::date() const noexcept
{
  return _date;
}


void DateTime::setDate(const Date& newDate) noexcept
{
  _date = newDate;
}


bool operator==(const Time& left, const Time& right) noexcept
{
  return left._hours == right._hours and left._minutes == right._minutes and left._seconds == right._seconds;
}


bool operator!=(const Time& left, const Time& right) noexcept
{
  return left._hours != right._hours or left._minutes != right._minutes or left._seconds != right._seconds;
}


bool operator<(const Time& left, const Time& right) noexcept
{
  if (left._hours < right._hours)
  {
    return true;
  }

  if (left._hours == right._hours)
  {
    if (left._minutes < right._minutes)
    {
      return true;
    }
    else if (left._minutes == right._minutes)
    {
      return left._seconds < right._seconds;
    }
  }

  return false;
}


bool operator==(const Date& left, const Date& right) noexcept
{
  return left._day == right._day and left._month == right._month and left._year == right._year;
}


bool operator!=(const Date& left, const Date& right) noexcept
{
  return left._day != right._day or left._month != right._month or left._year != right._year;
}


bool operator<(const Date& left, const Date& right) noexcept
{
  if (left._year < right._year)
  {
    return true;
  }
  else if (left._year == right._year)
  {
    if (static_cast<int>(left._month) < static_cast<int>(right._month))
    {
      return true;
    }
    else if (static_cast<int>(left._month) == static_cast<int>(right._month))
    {
      return left._day < right._day;
    }
  }
  return false;
}


bool operator==(const DateTime& left, const DateTime& right) noexcept
{
  return left._date == right._date and left._time == right._time;
}


bool operator!=(const DateTime& left, const DateTime& right) noexcept
{
  return left._date != right._date or left._time != right._time;
}


bool operator<(const DateTime& left, const DateTime& right) noexcept
{
  if (left._date < right._date)
  {
    return true;
  }
  else if (left._date == right._date)
  {
    return left._time < right._time;
  }

  return false;
}


namespace
{
template<typename value_type>
struct timed
{
  std::chrono::time_point<std::chrono::steady_clock> timestamp;
  value_type value;

  timed(const value_type& value) : value(value), timestamp(std::chrono::steady_clock::now())
  {
  }

  timed(value_type&& rvalue) : value(std::move(rvalue)), timestamp(std::chrono::steady_clock::now())
  {
  }
};


typedef timed<std::string> commitMessage;


constexpr int getWeekdayFromDays(int days)
{
  if (days >= -4)
    return (days + 4) % 7;
  else
    return (days + 5) % 7 + 6;
}


// From 1970-01-01 -> 0000-03-01
constexpr int shiftEpoch(int days)
{
  const int EpochShiftDays = 719468;
  return days + EpochShiftDays;
}


constexpr int getEraFromDays(int days)
{
  const int dEra = 365 * 400 + 97;
  return (days >= 0 ? days : days - (dEra - 1)) / dEra;
}


constexpr int getDayOfEra(int days, int era)
{
  const int dEra = 365 * 400 + 97;
  return days - era * dEra;
}


constexpr int getYearOfEra(int dayOfEra)
{
  const int d4Years = 365 * 4 + 1;
  const int d100Years = 365 * 100 + 24;
  const int d400Years = 365 * 400 + 97;

  const int adjustedDays = dayOfEra - dayOfEra / (d4Years - 1) + dayOfEra / d100Years - dayOfEra / (d400Years - 1);
  return adjustedDays / 365;
}


constexpr int getYDay(int dayOfEra, int yearOfEra)
{
  return dayOfEra - (365 * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
}


constexpr std::tuple<int, int, int, int> getYMDFromDays(int days)
{
  days = shiftEpoch(days);
  const int era = getEraFromDays(days);
  const int dayOfEra = getDayOfEra(days, era);
  const int yearOfEra = getYearOfEra(dayOfEra);
  const int shiftedYear = yearOfEra + era * 400;
  const int yday = getYDay(dayOfEra, yearOfEra);

  // dMarch + dApril + dMay + dJune + dJuly
  const int dToAugust = 31 + 30 + 31 + 30 + 31;
  const int shiftedMonth = (5 * yday + 2) / dToAugust;

  const int mday = yday - (dToAugust * shiftedMonth + 2) / 5 + 1;
  const int month = shiftedMonth + (shiftedMonth < 10 ? 3 : -9);
  const int year = shiftedYear + (month <= 2 ? 1 : 0);

  return std::tuple<int, int, int, int>(year, month, mday, yday);
}


std::tm toUTCTime(const std::chrono::system_clock::time_point& tp)
{
  using namespace std;
  using namespace chrono;
  typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;

  auto t = tp.time_since_epoch();
  days d = duration_cast<days>(t);
  t -= d;

  int year, month, mday, yday;
  std::tie(year, month, mday, yday) = getYMDFromDays(d.count());
  std::tm tm {};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_yday = yday;
  tm.tm_mday = mday;
  tm.tm_wday = getWeekdayFromDays(d.count());

  tm.tm_hour = static_cast<int>(duration_cast<hours>(t).count());
  t -= hours(tm.tm_hour);
  tm.tm_min = static_cast<int>(duration_cast<minutes>(t).count());
  t -= minutes(tm.tm_min);
  tm.tm_sec = static_cast<int>(duration_cast<seconds>(t).count());
  t -= seconds(tm.tm_sec);
  return tm;
}
}
