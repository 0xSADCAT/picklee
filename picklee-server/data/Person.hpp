#pragma once

#include <string>


class Convertor;


/// Общие данные для человека
class Person
{
public:
    static inline constexpr std::wstring_view className = L"Person";

    Person(const std::wstring& firstName, const std::wstring& lastName, const std::wstring& patronymic);

    const std::wstring& firstName() const;
    void setFirstName(const std::wstring& newFirstName);

    const std::wstring& lastName() const;
    void setLastName(const std::wstring& newLastName);

    const std::wstring& patronymic() const;
    void setPatronymic(const std::wstring& newPatronymic);

    /**
     * @brief Содержит ли имя, фамилия или отчество искомую строку
     * @param str Строка для поиска
     * @param cs Тип сравнения, по-умолчанию без учета регистра
     * @return true, если одно из трех содержит str
     */
    bool anyContains(const std::wstring& str) const;

    void convert(Convertor& conv);

private:
    std::wstring _firstName;
    std::wstring _lastName;
    std::wstring _patronymic;
};


/// Оператор
class Operator
{
public:
    static inline constexpr std::wstring_view className = L"Operator";

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
    static inline constexpr std::wstring_view className = L"Customer";

    Customer(int id, const Person& name);

    int id() const;

    const Person& name() const;
    void setName(const Person& newName);

    void convert(Convertor& conv);

private:
    int _id;
    Person _name;
};
