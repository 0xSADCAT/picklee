#pragma once

#include "Person.hpp"
#include "Product.hpp"

#include <QString>
#include <vector>


/// Заказ
class Order
{
public:
    /// Статус заказа
    enum class Status {
        InProcessing,       ///< В обработке
        WaitingForDelivery, ///< Ожидает поставки
        ReadyToIssue,       ///< Готов к выдаче
        Issued              ///< Выдано
    };

    Order(const QString& id, int operId, int customerId, const std::vector<ProductCount> products, Status status);

    const QString& id() const;

    const std::vector<ProductCount>& products() const;

    void addProduct(const ProductCount& product);

    Status status() const;
    void setStatus(Status newStatus);

private:
    QString _id;
    int _operId;
    int _customerId;
    std::vector<ProductCount> _products;
    Status _status;
};
