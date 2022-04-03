#include "Order.hpp"


Order::Order(const QString& id, int operId, int customerId, const QList<ProductCount> products, Status status)
    : _id(id),
      _operId(operId),
      _customerId(customerId),
      _products(products),
      _status(status)
{
}


const QString& Order::id() const
{
    return _id;
}


const QList<ProductCount>& Order::products() const
{
    return _products;
}


Order::Status Order::status() const
{
    return _status;
}


void Order::setStatus(Status newStatus)
{
    _status = newStatus;
}
