#include "Person.hpp"

#include "../utils/Utils.hpp"
#include "Constants.hpp"
#include "Convertor.hpp"

#include <algorithm>


Person::Person(const std::wstring& firstName, const std::wstring& lastName, const std::wstring& patronymic)
    : _firstName(firstName), _lastName(lastName), _patronymic(patronymic)
{
}


const std::wstring& Person::firstName() const
{
  return _firstName;
}


void Person::setFirstName(const std::wstring& newFirstName)
{
  _firstName = newFirstName;
}


const std::wstring& Person::lastName() const
{
  return _lastName;
}


void Person::setLastName(const std::wstring& newLastName)
{
  _lastName = newLastName;
}


const std::wstring& Person::patronymic() const
{
  return _patronymic;
}


void Person::setPatronymic(const std::wstring& newPatronymic)
{
  _patronymic = newPatronymic;
}


bool Person::anyContains(const std::wstring& str) const
{
  return util::str::contains(_firstName, str) or util::str::contains(_lastName, str)
         or util::str::contains(_patronymic, str);
}


void Person::convert(Convertor& conv)
{
  conv.beginBlock(className);
  conv.field(fn::firstName, _firstName);
  conv.field(fn::lastName, _lastName);
  conv.field(fn::patronymic, _patronymic);
  conv.endBlock(className);
}


Operator::Operator(int id, const Person& name) : _id(id), _name(name)
{
}


const Person& Operator::name() const
{
  return _name;
}


void Operator::setName(const Person& newName)
{
  _name = newName;
}


int Operator::id() const
{
  return _id;
}


void Operator::convert(Convertor& conv)
{
  conv.beginBlock(className);
  conv.field(fn::id, std::to_wstring(_id));
  _name.convert(conv);
  conv.endBlock(className);
}


Customer::Customer(int id, const Person& name) : _id(id), _name(name)
{
}


int Customer::id() const
{
  return _id;
}


const Person& Customer::name() const
{
  return _name;
}


void Customer::setName(const Person& newName)
{
  _name = newName;
}


void Customer::convert(Convertor& conv)
{
  conv.beginBlock(className);
  conv.field(fn::id, std::to_wstring(_id));
  _name.convert(conv);
  conv.endBlock(className);
}
