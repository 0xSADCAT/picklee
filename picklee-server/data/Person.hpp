#pragma once

#include <string>


class Convertor;


/// Общие данные для человека
class Person
{
public:
  static inline constexpr std::wstring_view className = L"Person";

  Person(const std::wstring& firstName, const std::wstring& lastName, const std::wstring& patronymic) noexcept;

  const std::wstring& firstName() const noexcept;
  void setFirstName(const std::wstring& newFirstName) noexcept;

  const std::wstring& lastName() const noexcept;
  void setLastName(const std::wstring& newLastName) noexcept;

  const std::wstring& patronymic() const noexcept;
  void setPatronymic(const std::wstring& newPatronymic) noexcept;

  /**
   * @brief Содержит ли имя, фамилия или отчество искомую строку
   * @param str Строка для поиска
   * @param cs Тип сравнения, по-умолчанию без учета регистра
   * @return true, если одно из трех содержит str
   */
  bool anyContains(const std::wstring& str) const noexcept;

  void convert(Convertor& conv) noexcept;

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

  Operator(int id, const Person& name) noexcept;

  const Person& name() const noexcept;
  void setName(const Person& newName) noexcept;

  int id() const noexcept;

  void convert(Convertor& conv) noexcept;

private:
  int _id;
  Person _name;
};


/// Заказчик
class Customer
{
public:
  static inline constexpr std::wstring_view className = L"Customer";

  Customer(int id, const Person& name) noexcept;

  int id() const noexcept;

  const Person& name() const noexcept;
  void setName(const Person& newName) noexcept;

  void convert(Convertor& conv) noexcept;

private:
  int _id;
  Person _name;
};
