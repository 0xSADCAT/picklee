#include "Warehouse.hpp"

#include "Constants.hpp"

#include <algorithm>
#include <cassert>
#include <regex>


namespace
{

const static auto wrap = [](const std::wstring& str) {
  return L"\"" + str + L"\"";
};

}


Warehouse::Warehouse(int id, int priority, const std::wstring& description) noexcept
    : _id(id), _priority(priority), _description(description)
{
}


Warehouse Warehouse::fromString(const std::wstring& string)
{
}


std::wstring Warehouse::toString() const noexcept
{
}


int Warehouse::priority() const noexcept
{
  return _priority;
}


void Warehouse::setPriority(int newPriority) noexcept
{
  _priority = newPriority;
}


const std::wstring& Warehouse::description() const noexcept
{
  return _description;
}


void Warehouse::setDescription(const std::wstring& newDescription) noexcept
{
  _description = newDescription;
}


const std::vector<ProductCount>& Warehouse::products() const noexcept
{
  return _products;
}


void Warehouse::deliver(const ProductCount& product) noexcept
{
  assert(product.count() > 0);

  auto iter = std::find_if(_products.begin(), _products.end(), [&](const ProductCount& each) noexcept {
    return each.code() == product.code();
  });

  if (iter == _products.end())
  {
    _products.push_back(product);
  }
  else
  {
    iter->countRef() += product.count();
  }
}


bool Warehouse::fetch(const ProductCount& product) noexcept
{
  assert(product.count() > 0);

  auto iter = std::find_if(_products.begin(), _products.end(), [&](const ProductCount& each) noexcept {
    return each.code() == product.code();
  });

  if (iter == _products.end())
  {
    return false;
  }

  iter->countRef() -= product.count();

  if (iter->count() == 0)
  {
    _products.erase(iter);
  }

  return true;
}


bool Warehouse::canFetch(const ProductCount& product) const noexcept
{
  assert(product.count() > 0);

  auto iter = std::find_if(_products.begin(), _products.end(), [&](const ProductCount& each) noexcept {
    return each.code() == product.code();
  });

  if (iter == _products.end())
  {
    return false;
  }
  else
  {
    return iter->count() >= product.count();
  }
}


int Warehouse::id() const noexcept
{
  return _id;
}
