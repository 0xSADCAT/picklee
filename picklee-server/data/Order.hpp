#pragma once

#include "Person.hpp"
#include "Product.hpp"

#include <QList>
#include <QString>


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

    Order(const QString& id, int operId, int customerId, const QList<ProductCount> products, Status status);

    const QString& id() const;

    const QList<ProductCount>& products() const;

    Status status() const;
    void setStatus(Status newStatus);

private:
    QString _id;
    int _operId;
    int _customerId;
    QList<ProductCount> _products;
    Status _status;
};
