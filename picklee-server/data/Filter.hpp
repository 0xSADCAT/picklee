#pragma once

#include <string>


class Order;
class Customer;
class Operator;
class ProductCount;
class ProductDescription;
class VendorCode;


/**
 * @brief Базовый фильтр для поиска
 *
 * @details Является базовым классом для всех фильтров.
 *          Ничего не фильтрует, может использоваться для операций "получить все"
 */
class Filter
{
public:
  Filter() noexcept = default;
  virtual ~Filter() noexcept = default;

  virtual bool filter(const Order&) const noexcept
  {
    return true;
  }

  virtual bool filter(const Customer&) const noexcept
  {
    return true;
  }

  virtual bool filter(const Operator&) const noexcept
  {
    return true;
  }

  virtual bool filter(const ProductCount&) const noexcept
  {
    return true;
  }

  virtual bool filter(const ProductDescription&) const noexcept
  {
    return true;
  }
};


/// Фильтр "содержит"
class FilterContains : public Filter
{
public:
  /**
   * @brief Фильтр "содержит"
   * @param str Строка для поиска
   */
  FilterContains(const std::wstring& str) noexcept;

  virtual bool filter(const Order& order) const noexcept override;
  virtual bool filter(const Customer& customer) const noexcept override;
  virtual bool filter(const Operator& oper) const noexcept override;
  virtual bool filter(const ProductCount& product) const noexcept override;
  virtual bool filter(const ProductDescription& product) const noexcept override;

private:
  const std::wstring _str;
};


/// Фильтр по идентификатору
class FilterId : public Filter
{
public:
  /**
   * @brief Фильтр по идентификатору
   * @param id Идентификатор
   *
   * @details Фильтрует по идентификатору. Все классы, кроме заказов - точное соответствие,
   *          заказы по принципу "содержит в себе"
   */
  FilterId(int id) noexcept;

  /**
   * @brief Фильтр по идентификатору
   * @param id Текстовый идентификатор
   *
   * @details Фильтрует по идентификатору. Создавая данным конструктором фильтр полностью
   *          исключает все, кроме заказов.
   */
  FilterId(const std::wstring& id) noexcept;

  virtual bool filter(const Order& order) const noexcept override;
  virtual bool filter(const Customer& customer) const noexcept override;
  virtual bool filter(const Operator& oper) const noexcept override;
  virtual bool filter(const ProductCount&) const noexcept override;
  virtual bool filter(const ProductDescription&) const noexcept override;

private:
  const std::wstring _str;
  const int _id;
  const bool _ordersOnly;
};


/// Фильтр по артикулу
class FilterVendorCode : public Filter
{
public:
  /**
   * @brief Фильтр точного соответствия артикула
   * @param code Артикул
   */
  FilterVendorCode(const VendorCode& code) noexcept;

  /**
   * @brief Фильтр частичного соответствия артикула
   * @param str Часть артикула
   */
  FilterVendorCode(const std::wstring& str) noexcept;

  virtual bool filter(const Order& order) const noexcept override;
  virtual bool filter(const Customer&) const noexcept override;
  virtual bool filter(const Operator&) const noexcept override;
  virtual bool filter(const ProductCount& product) const noexcept override;
  virtual bool filter(const ProductDescription& product) const noexcept override;

private:
  const std::wstring _code;
  const bool _partical;
};
