#pragma once

#include <QString>


/// Общие данные для человека
class Person
{
public:
    Person(const QString& firstName, const QString& lastName, const QString& patronymic);

    const QString& firstName() const;
    void setFirstName(const QString& newFirstName);

    const QString& lastName() const;
    void setLastName(const QString& newLastName);

    const QString& patronymic() const;
    void setPatronymic(const QString& newPatronymic);

    /**
     * @brief Содержит ли имя, фамилия или отчество искомую строку
     * @param str Строка для поиска
     * @param cs Тип сравнения, по-умолчанию без учета регистра
     * @return true, если одно из трех содержит str
     */
    bool anyContains(const QString& str, Qt::CaseSensitivity cs = Qt::CaseInsensitive) const;

private:
    QString _firstName;
    QString _lastName;
    QString _patronymic;
};


/// Оператор
class Operator
{
public:
    Operator(int id, const Person& name);

    const Person& name() const;
    void setName(const Person& newName);

    int id() const;

private:
    int _id;
    Person _name;
};


/// Заказчик
class Customer
{
public:
    Customer(int id, const Person& name);

    int id() const;

    const Person& name() const;
    void setName(const Person& newName);

private:
    int _id;
    Person _name;
};
