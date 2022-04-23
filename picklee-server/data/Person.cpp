#include "Person.hpp"

#include "../utils/Utils.hpp"
#include "Exceptions.hpp"

#include <algorithm>
#include <regex>


namespace
{

const static auto wrap = [](const std::wstring& str) {
  return L"\"" + str + L"\"";
};

}


Person::Person(const std::wstring& firstName, const std::wstring& lastName, const std::wstring& patronymic) noexcept
    : _firstName(firstName), _lastName(lastName), _patronymic(patronymic)
{
}


Person Person::fromString(const std::wstring& string)
{
  const static std::wregex expr(std::wstring(className)
                                + L"\\s*\\{\\s*\"([^\"]+)\"\\s*,?\\s*\"([^\"]+)\"\\s*,?\\s*\"([^\"]+)\",?\\s*\\}\\s*");
  std::wsmatch match;
  if (std::regex_search(string, match, expr))
  {
    return Person(match[1].str(), match[2].str(), match[3].str());
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring Person::toString() const noexcept
{
  return std::wstring(className) + L" { " + wrap(_firstName) + L", " + wrap(_lastName) + L", " + wrap(_patronymic)
         + L" }";
}


const std::wstring& Person::firstName() const noexcept
{
  return _firstName;
}


void Person::setFirstName(const std::wstring& newFirstName) noexcept
{
  _firstName = newFirstName;
}


const std::wstring& Person::lastName() const noexcept
{
  return _lastName;
}


void Person::setLastName(const std::wstring& newLastName) noexcept
{
  _lastName = newLastName;
}


const std::wstring& Person::patronymic() const noexcept
{
  return _patronymic;
}


void Person::setPatronymic(const std::wstring& newPatronymic) noexcept
{
  _patronymic = newPatronymic;
}


bool Person::anyContains(const std::wstring& str) const noexcept
{
  return util::str::contains(_firstName, str) or util::str::contains(_lastName, str)
         or util::str::contains(_patronymic, str);
}


Operator::Operator(int id, const Person& name) noexcept : _id(id), _name(name)
{
}


Operator Operator::fromString(const std::wstring& string)
{
  const static std::wregex expr(std::wstring(className) + L"\\s*\\{\\s*\"(\\d+)\"\\s*,?\\s*("
                                + std::wstring(Person::className) + L"\\s*\\{.*\\})" + L"\\s*\\}\\s*");
  std::wsmatch match;

  if (std::regex_search(string, match, expr))
  {
    return Operator(std::stoi(match[1].str()), Person::fromString(match[2].str()));
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring Operator::toString() const noexcept
{
  return std::wstring(className) + L" { " + wrap(std::to_wstring(_id)) + L", " + _name.toString() + L" }";
}


const Person& Operator::name() const noexcept
{
  return _name;
}


void Operator::setName(const Person& newName) noexcept
{
  _name = newName;
}


int Operator::id() const noexcept
{
  return _id;
}


Customer::Customer(int id, const Person& name) noexcept : _id(id), _name(name)
{
}


Customer Customer::fromString(const std::wstring& string)
{
  const static std::wregex expr(std::wstring(className) + L"\\s*\\{\\s*\"(\\d+)\"\\s*,?\\s*("
                                + std::wstring(Person::className) + L"\\s*\\{.*\\})" + L"\\s*\\}\\s*");
  std::wsmatch match;

  if (std::regex_search(string, match, expr))
  {
    return Customer(std::stoi(match[1].str()), Person::fromString(match[2].str()));
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring Customer::toString() const noexcept
{
  return std::wstring(className) + L" { " + wrap(std::to_wstring(_id)) + L", " + _name.toString() + L" }";
}


int Customer::id() const noexcept
{
  return _id;
}


const Person& Customer::name() const noexcept
{
  return _name;
}


void Customer::setName(const Person& newName) noexcept
{
  _name = newName;
}
