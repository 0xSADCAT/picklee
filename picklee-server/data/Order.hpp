#pragma once

#include "Person.hpp"
#include "Product.hpp"

#include <string>
#include <vector>


class Convertor;


/// Заказ
class Order
{
public:
  static inline constexpr std::wstring_view className = L"Order";

  /// Статус заказа
  enum class Status
  {
    InProcessing,       ///< В обработке
    WaitingForDelivery, ///< Ожидает поставки
    ReadyToIssue,       ///< Готов к выдаче
    Issued              ///< Выдано
  };

  Order(const std::wstring& id, int operId, int customerId, const std::vector<ProductCount> products, Status status);

  const std::wstring& id() const;

  const std::vector<ProductCount>& products() const;

  void addProduct(const ProductCount& product);

  Status status() const;
  void setStatus(Status newStatus);

  void convert(Convertor& convertor) const;

private:
  std::wstring _id;
  int _operId;
  int _customerId;
  std::vector<ProductCount> _products;
  Status _status;
};
