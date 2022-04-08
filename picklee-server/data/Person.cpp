#include "Person.hpp"


Person::Person(const QString& firstName, const QString& lastName, const QString& patronymic)
    : _firstName(firstName),
      _lastName(lastName),
      _patronymic(patronymic)
{
}


const QString& Person::firstName() const
{
    return _firstName;
}


void Person::setFirstName(const QString& newFirstName)
{
    _firstName = newFirstName;
}


const QString& Person::lastName() const
{
    return _lastName;
}


void Person::setLastName(const QString& newLastName)
{
    _lastName = newLastName;
}


const QString& Person::patronymic() const
{
    return _patronymic;
}


void Person::setPatronymic(const QString& newPatronymic)
{
    _patronymic = newPatronymic;
}


bool Person::anyContains(const QString& str, Qt::CaseSensitivity cs) const
{
    return _firstName.contains(str, cs) or _lastName.contains(str, cs) or _patronymic.contains(str, cs);
}


Operator::Operator(int id, const Person& name)
    : _id(id),
      _name(name)
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


Customer::Customer(int id, const Person& name)
    : _id(id),
      _name(name)
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
