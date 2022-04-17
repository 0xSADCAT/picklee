#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <string>
#include <vector>


/// Интерфейс парсера строк в объекты базы данных
class I_Parser
{
public:
  I_Parser() noexcept = default;
  virtual ~I_Parser() noexcept = default;

  /// Передать строку для парсинга
  virtual void parse(const std::wstring& string) noexcept = 0;

  /// Получить копию результатов с заказами
  virtual std::vector<Order> orders() const noexcept = 0;

  /// Получить копию результатов с операторами
  virtual std::vector<Operator> operators() const noexcept = 0;

  /// Получить копию результатов с заказчиками
  virtual std::vector<Customer> customers() const noexcept = 0;

  /// Получить копию результатов с описаниями
  virtual std::vector<ProductDescription> descriptions() const noexcept = 0;

  /// Получить копию результатов со складами
  virtual std::vector<Warehouse> warehouses() const noexcept = 0;

  /**
   * @brief Загрузить полученные заказы в контейнер
   * @param inserter Итератор вставки в контейнер
   */
  virtual void loadTo(std::back_insert_iterator<std::vector<Order>> inserter) const noexcept = 0;

  /**
   * @brief Загрузить полученных операторов в контейнер
   * @param inserter Итератор вставки в контейнер
   */
  virtual void loadTo(std::back_insert_iterator<std::vector<Operator>> inserter) const noexcept = 0;

  /**
   * @brief Загрузить полученных заказчиков в контейнер
   * @param inserter Итератор вставки в контейнер
   */
  virtual void loadTo(std::back_insert_iterator<std::vector<Customer>> inserter) const noexcept = 0;

  /**
   * @brief Загрузить полученные описания в контейнер
   * @param inserter Итератор вставки в контейнер
   */
  virtual void loadTo(std::back_insert_iterator<std::vector<ProductDescription>> inserter) const noexcept = 0;

  /**
   * @brief Загрузить полученные склады в контейнер
   * @param inserter Итератор вставки в контейнер
   */
  virtual void loadTo(std::back_insert_iterator<std::vector<Warehouse>> inserter) const noexcept = 0;

  /// Получить список ошибок парминга
  virtual std::vector<std::pair<std::wstring_view, std::wstring>> errors() const noexcept = 0;

  /// Очистить результаты и списки
  virtual void clear() noexcept = 0;
};
