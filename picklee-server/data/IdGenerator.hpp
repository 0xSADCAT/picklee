#pragma once

#include <string>
#include <tuple>


class Operator;
class Customer;


/// Генератор идендификаторов
class IdGenerator
{
public:
  IdGenerator() noexcept;

  int generateClient() noexcept;
  int generateOperator() noexcept;
  int generateWarehouse() noexcept;

  static std::wstring generateOrder(const Operator& oper, const Customer& customer) noexcept;

  /**
   * @brief Установить новые значения счетчиков идентификаторов
   * @param oper Для операторов
   * @param client Для клиентов
   * @param warehouse Для складов
   */
  void reset(int oper, int client, int warehouse) noexcept;

  /**
   * @brief Получить текущие значения счетчиков
   * @return Счетчики для: <оператор, клиент, склад>
   */
  std::tuple<int, int, int> getAll() const noexcept;

private:
  int _oper;
  int _client;
  int _warehouse;
};
