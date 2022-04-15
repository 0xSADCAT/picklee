#pragma once

#include "Product.hpp"

#include <string>
#include <vector>


class Convertor;


class Warehouse
{
public:
  static inline constexpr std::wstring_view className = L"Warehouse";

  Warehouse(int id, int priority, const std::wstring& description);

  int priority() const;
  void setPriority(int newPriority);

  const std::wstring& description() const;
  void setDescription(const std::wstring& newDescription);

  /// Состав склада (только для чтения)
  const std::vector<ProductCount>& products() const;

  /**
   * @brief Поставить продукт на склад
   * @param product Продукт для поставки
   *
   * @note Условие: product.count() > 0
   */
  void deliver(const ProductCount& product);

  /**
   * @brief Взять продукт со склада
   * @param product Продукт
   * @return false если на складе недостаточное количество
   *
   * @note Условие: product.count() > 0
   */
  bool fetch(const ProductCount& product);

  /**
   * @brief Можно ли взять продукт со склада
   * @param product Продукт
   * @return true если количество на складе позволяет
   *
   * @note Условие: product.count() > 0
   */
  bool canFetch(const ProductCount& product) const;

  int id() const;

  void convert(Convertor& conv);

private:
  int _id;                             ///< Идентификатор
  int _priority;                       ///< Приоритет
  std::wstring _description;           ///< Описание
  std::vector<ProductCount> _products; ///< Состав склада
};
