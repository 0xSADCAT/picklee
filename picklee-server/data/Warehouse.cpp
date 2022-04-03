#include "Warehouse.hpp"


Warehouse::Warehouse(int priority, const QString& description)
    : _priority(priority),
      _description(description)
{
}


int Warehouse::priority() const
{
    return _priority;
}


void Warehouse::setPriority(int newPriority)
{
    _priority = newPriority;
}


const QString& Warehouse::description() const
{
    return _description;
}


void Warehouse::setDescription(const QString& newDescription)
{
    _description = newDescription;
}


const QList<ProductCount>& Warehouse::products() const
{
    return _products;
}


void Warehouse::deliver(const ProductCount& product)
{
    assert(product.count() > 0);

    auto iter = std::find(_products.begin(), _products.end(), [&](const ProductCount& each) {
        return each.code() == product.code();
    });

    if (iter == _products.end()) {
        _products.append(product);
    } else {
        iter->countRef() += product.count();
    }
}


bool Warehouse::fetch(const ProductCount& product)
{
    assert(product.count() > 0);

    auto iter = std::find(_products.begin(), _products.end(), [&](const ProductCount& each) {
        return each.code() == product.code();
    });

    if (iter == _products.end()) {
        return false;
    }

    iter->countRef() -= product.count();

    if (iter->count() == 0) {
        _products.erase(iter);
    }

    return true;
}


bool Warehouse::canFetch(const ProductCount& product) const
{
    assert(product.count() > 0);

    auto iter = std::find(_products.begin(), _products.end(), [&](const ProductCount& each) {
        return each.code() == product.code();
    });

    if (iter == _products.end()) {
        return false;
    } else {
        return iter->count() >= product.count();
    }
}
