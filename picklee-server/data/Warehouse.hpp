#pragma once

#include "Product.hpp"

#include <string>
#include <vector>


class Convertor;


class Warehouse
{
public:
  static inline constexpr std::wstring_view className = L"Warehouse";

  Warehouse(int id, int priority, const std::wstring& description) noexcept;

  int priority() const noexcept;
  void setPriority(int newPriority) noexcept;

  const std::wstring& description() const noexcept;
  void setDescription(const std::wstring& newDescription) noexcept;

  /// Состав склада (только для чтения)
  const std::vector<ProductCount>& products() const noexcept;

  /**
   * @brief Поставить продукт на склад
   * @param product Продукт для поставки
   *
   * @note Условие: product.count() > 0
   */
  void deliver(const ProductCount& product) noexcept;

  /**
   * @brief Взять продукт со склада
   * @param product Продукт
   * @return false если на складе недостаточное количество
   *
   * @note Условие: product.count() > 0
   */
  bool fetch(const ProductCount& product) noexcept;

  /**
   * @brief Можно ли взять продукт со склада
   * @param product Продукт
   * @return true если количество на складе позволяет
   *
   * @note Условие: product.count() > 0
   */
  bool canFetch(const ProductCount& product) const noexcept;

  int id() const noexcept;

  void convert(Convertor& conv) noexcept;

private:
  int _id;                             ///< Идентификатор
  int _priority;                       ///< Приоритет
  std::wstring _description;           ///< Описание
  std::vector<ProductCount> _products; ///< Состав склада
};
