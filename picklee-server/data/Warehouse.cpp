#include "Warehouse.hpp"

#include "Exceptions.hpp"

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


Warehouse Warehouse::fromString(std::wstring string)
{
  const static std::wregex expr(
      std::wstring(className)
      + L"\\s*\\{\\s*\"(\\d+)\"\\s*,?\\s*\"(-?\\d+)\"\\s*,?\\s*\"([^\"]+)\"\\s*,?\\s*\\[(.*)\\]\\s*\\}");
  const static std::wregex countExpr(L"(" + std::wstring(ProductCount::className) + L"\\s*\\{\\s*[^\\{]+\\s*\\})");

  for (auto&& ch : string)
  {
    if (ch == L'\n')
    {
      ch = L' ';
    }
  }

  std::wsmatch match;
  if (std::regex_search(string, match, expr))
  {
    int id = std::stoi(match[1].str());
    int priority = std::stoi(match[2].str());
    std::wstring description = match[3].str();

    std::vector<ProductCount> products;
    std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), countExpr},
                                       std::wsregex_iterator {}};
    for (auto&& each : matches)
    {
      products.push_back(ProductCount::fromString(each[1].str()));
    }

    Warehouse result(id, priority, description);
    result._products = std::move(products);
    return result;
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring Warehouse::toString() const noexcept
{
  std::wstring result(className);

  result += L" {\n" + wrap(std::to_wstring(_id)) + L", " + wrap(std::to_wstring(_priority)) + L", " + wrap(_description)
            + L",\n  [\n";

  for (auto&& prod : _products)
  {
    result += L"  " + prod.toString() + L"\n";
  }

  result += L"  ]\n}";

  return result;
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
