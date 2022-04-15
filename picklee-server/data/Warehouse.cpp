#include "Warehouse.hpp"

#include "Constants.hpp"
#include "Convertor.hpp"

#include <algorithm>
#include <cassert>


Warehouse::Warehouse(int id, int priority, const std::wstring& description)
    : _id(id), _priority(priority), _description(description)
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


const std::wstring& Warehouse::description() const
{
  return _description;
}


void Warehouse::setDescription(const std::wstring& newDescription)
{
  _description = newDescription;
}


const std::vector<ProductCount>& Warehouse::products() const
{
  return _products;
}


void Warehouse::deliver(const ProductCount& product)
{
  assert(product.count() > 0);

  auto iter = std::find_if(
      _products.begin(), _products.end(), [&](const ProductCount& each) { return each.code() == product.code(); });

  if (iter == _products.end())
  {
    _products.push_back(product);
  }
  else
  {
    iter->countRef() += product.count();
  }
}


bool Warehouse::fetch(const ProductCount& product)
{
  assert(product.count() > 0);

  auto iter = std::find_if(
      _products.begin(), _products.end(), [&](const ProductCount& each) { return each.code() == product.code(); });

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


bool Warehouse::canFetch(const ProductCount& product) const
{
  assert(product.count() > 0);

  auto iter = std::find_if(
      _products.begin(), _products.end(), [&](const ProductCount& each) { return each.code() == product.code(); });

  if (iter == _products.end())
  {
    return false;
  }
  else
  {
    return iter->count() >= product.count();
  }
}


int Warehouse::id() const
{
  return _id;
}


void Warehouse::convert(Convertor& conv)
{
  conv.beginBlock(className);
  conv.field(fn::id, std::to_wstring(_id));
  conv.field(fn::priority, std::to_wstring(_priority));
  conv.field(fn::description, _description);

  conv.beginBlock(_products.data()->className);
  for (auto&& prod : _products)
  {
    prod.convert(conv);
  }
  conv.endBlock(_products.data()->className);

  conv.endBlock(className);
}
