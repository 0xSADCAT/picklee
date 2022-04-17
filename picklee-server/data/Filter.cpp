#include "Filter.hpp"

#include "../utils/Utils.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"


FilterContains::FilterContains(const std::wstring& str) noexcept : _str(str)
{
}


bool FilterContains::filter(const Order& order) const noexcept
{
  for (auto&& product : order.products())
  {
    if (filter(product))
    {
      return true;
    }
  }

  return false;
}


bool FilterContains::filter(const Customer& customer) const noexcept
{
  return customer.name().anyContains(_str);
}


bool FilterContains::filter(const Operator& oper) const noexcept
{
  return oper.name().anyContains(_str);
}


bool FilterContains::filter(const ProductCount& product) const noexcept
{
  return util::str::contains(product.code().str().data(), _str.data());
}


bool FilterContains::filter(const ProductDescription& product) const noexcept
{
  return util::str::contains(product.code().str().data(), _str.data())
         or util::str::contains(product.description().data(), _str.data());
}

FilterId::FilterId(int id) noexcept : _str(std::to_wstring(id)), _id(id), _ordersOnly(false)
{
}


FilterId::FilterId(const std::wstring& id) noexcept : _str(id), _id(-1), _ordersOnly(true)
{
}


bool FilterId::filter(const Order& order) const noexcept
{
  return util::str::contains(order.id().data(), _str.data());
}


bool FilterId::filter(const Customer& customer) const noexcept
{
  if (_ordersOnly)
  {
    return false;
  }

  return customer.id() == _id;
}


bool FilterId::filter(const Operator& oper) const noexcept
{
  if (_ordersOnly)
  {
    return false;
  }

  return oper.id() == _id;
}


bool FilterId::filter(const ProductCount&) const noexcept
{
  return false;
}


bool FilterId::filter(const ProductDescription&) const noexcept
{
  return false;
}


FilterVendorCode::FilterVendorCode(const VendorCode& code) noexcept : _code(code.str()), _partical(false)
{
}


FilterVendorCode::FilterVendorCode(const std::wstring& str) noexcept : _code(str), _partical(true)
{
}


bool FilterVendorCode::filter(const Order& order) const noexcept
{
  for (auto&& prod : order.products())
  {
    if (filter(prod))
    {
      return true;
    }
  }

  return false;
}


bool FilterVendorCode::filter(const Customer&) const noexcept
{
  return false;
}


bool FilterVendorCode::filter(const Operator&) const noexcept
{
  return false;
}


bool FilterVendorCode::filter(const ProductCount& product) const noexcept
{
  if (_partical)
  {
    return util::str::contains(product.code().str().data(), _code.data());
  }
  else
  {
    return product.code().str() == _code;
  }
}


bool FilterVendorCode::filter(const ProductDescription& product) const noexcept
{
  if (_partical)
  {
    return util::str::contains(product.code().str().data(), _code.data());
  }
  else
  {
    return product.code().str() == _code;
  }
}
