#include "Order.hpp"


Order::Order(const QString& id, int operId, int customerId, const std::vector<ProductCount> products, Status status)
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


const std::vector<ProductCount>& Order::products() const
{
    return _products;
}

void Order::addProduct(const ProductCount& product)
{
    assert(product.count() > 0);

    auto iter = std::find_if(_products.begin(), _products.end(), [&product](const ProductCount& prod) {
        return prod.code() == product.code();
    });

    if (iter != _products.end()) {
        iter->countRef() += product.count();
    } else {
        _products.push_back(product);
    }
}


Order::Status Order::status() const
{
    return _status;
}


void Order::setStatus(Status newStatus)
{
    _status = newStatus;
}
