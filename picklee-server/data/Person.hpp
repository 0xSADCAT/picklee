#pragma once

#include <QString>


class Convertor;


/// Общие данные для человека
class Person
{
public:
    static inline const QString className = "Person";

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

    void convert(Convertor& conv);

private:
    QString _firstName;
    QString _lastName;
    QString _patronymic;
};


/// Оператор
class Operator
{
public:
    static inline const QString className = "Operator";

    Operator(int id, const Person& name);

    const Person& name() const;
    void setName(const Person& newName);

    int id() const;

    void convert(Convertor& conv);

private:
    int _id;
    Person _name;
};


/// Заказчик
class Customer
{
public:
    static inline const QString className = "Customer";

    Customer(int id, const Person& name);

    int id() const;

    const Person& name() const;
    void setName(const Person& newName);

    void convert(Convertor& conv);

private:
    int _id;
    Person _name;
};
