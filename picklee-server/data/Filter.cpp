#include "Filter.hpp"

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"


FilterContains::FilterContains(const QString& str, bool strongCase)
    : _str(str),
      _cs(strongCase ? Qt::CaseSensitive : Qt::CaseInsensitive)
{
}


bool FilterContains::filter(const Order& order) const
{
    for (auto&& product : order.products()) {
        if (filter(product)) {
            return true;
        }
    }

    return false;
}


bool FilterContains::filter(const Customer& customer) const
{
    return customer.name().anyContains(_str, _cs);
}


bool FilterContains::filter(const Operator& oper) const
{
    return oper.name().anyContains(_str, _cs);
}


bool FilterContains::filter(const ProductCount& product) const
{
    return product.code().str().contains(_str, _cs);
}


bool FilterContains::filter(const ProductDescription& product) const
{
    return product.code().str().contains(_str, _cs) or product.description().contains(_str, _cs);
}

FilterId::FilterId(int id)
    : _str(QString::number(id)),
      _id(id),
      _ordersOnly(false)
{
}


FilterId::FilterId(const QString& id)
    : _str(id),
      _id(-1),
      _ordersOnly(true)
{
}


bool FilterId::filter(const Order& order) const
{
    return order.id().contains(_str);
}


bool FilterId::filter(const Customer& customer) const
{
    if (_ordersOnly) {
        return false;
    }

    return customer.id() == _id;
}


bool FilterId::filter(const Operator& oper) const
{
    if (_ordersOnly) {
        return false;
    }

    return oper.id() == _id;
}


bool FilterId::filter(const ProductCount&) const
{
    return false;
}


bool FilterId::filter(const ProductDescription&) const
{
    return false;
}


FilterVendorCode::FilterVendorCode(const VendorCode& code)
    : _code(code.str()),
      _partical(false)
{
}


FilterVendorCode::FilterVendorCode(const QString& str)
    : _code(str),
      _partical(true)
{
}


bool FilterVendorCode::filter(const Order& order) const
{
    for (auto&& prod : order.products()) {
        if (filter(prod)) {
            return true;
        }
    }

    return false;
}


bool FilterVendorCode::filter(const Customer&) const
{
    return false;
}


bool FilterVendorCode::filter(const Operator&) const
{
    return false;
}


bool FilterVendorCode::filter(const ProductCount& product) const
{
    if (_partical) {
        return product.code().str().contains(_code);
    } else {
        return product.code().str() == _code;
    }
}


bool FilterVendorCode::filter(const ProductDescription& product) const
{
    if (_partical) {
        return product.code().str().contains(_code);
    } else {
        return product.code().str() == _code;
    }
}
