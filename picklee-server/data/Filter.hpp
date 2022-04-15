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
  Filter() = default;
  virtual ~Filter() = default;

  virtual bool filter(const Order&) const
  {
    return true;
  }

  virtual bool filter(const Customer&) const
  {
    return true;
  }

  virtual bool filter(const Operator&) const
  {
    return true;
  }

  virtual bool filter(const ProductCount&) const
  {
    return true;
  }

  virtual bool filter(const ProductDescription&) const
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
  FilterContains(const std::wstring& str);

  virtual bool filter(const Order& order) const override;
  virtual bool filter(const Customer& customer) const override;
  virtual bool filter(const Operator& oper) const override;
  virtual bool filter(const ProductCount& product) const override;
  virtual bool filter(const ProductDescription& product) const override;

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
  FilterId(int id);

  /**
   * @brief Фильтр по идентификатору
   * @param id Текстовый идентификатор
   *
   * @details Фильтрует по идентификатору. Создавая данным конструктором фильтр полностью
   *          исключает все, кроме заказов.
   */
  FilterId(const std::wstring& id);

  virtual bool filter(const Order& order) const override;
  virtual bool filter(const Customer& customer) const override;
  virtual bool filter(const Operator& oper) const override;
  virtual bool filter(const ProductCount&) const override;
  virtual bool filter(const ProductDescription&) const override;

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
  FilterVendorCode(const VendorCode& code);

  /**
   * @brief Фильтр частичного соответствия артикула
   * @param str Часть артикула
   */
  FilterVendorCode(const std::wstring& str);

  virtual bool filter(const Order& order) const override;
  virtual bool filter(const Customer&) const override;
  virtual bool filter(const Operator&) const override;
  virtual bool filter(const ProductCount& product) const override;
  virtual bool filter(const ProductDescription& product) const override;

private:
  const std::wstring _code;
  const bool _partical;
};
