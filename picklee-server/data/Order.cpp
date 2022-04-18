#include "Order.hpp"

#include "Constants.hpp"
#include "Convertor.hpp"

#include <algorithm>
#include <cassert>


Order::Order(const std::wstring& id,
             int operId,
             int customerId,
             const std::vector<ProductCount> products,
             Status status) noexcept
    : _id(id), _operId(operId), _customerId(customerId), _products(products), _status(status)
{
}


const std::wstring& Order::id() const noexcept
{
  return _id;
}


const std::vector<ProductCount>& Order::products() const noexcept
{
  return _products;
}

void Order::addProduct(const ProductCount& product) noexcept
{
  assert(product.count() > 0);

  auto iter = std::find_if(_products.begin(), _products.end(), [&product](const ProductCount& prod) {
    return prod.code() == product.code();
  });

  if (iter != _products.end())
  {
    iter->countRef() += product.count();
  }
  else
  {
    _products.push_back(product);
  }
}


Order::Status Order::status() const noexcept
{
  return _status;
}


void Order::setStatus(Status newStatus) noexcept
{
  _status = newStatus;
}


void Order::convert(Convertor& convertor) const noexcept
{
  std::wstring_view status;
  switch (_status)
  {
  case Status::InProcessing:
    status = L"InProcessing";
    break;

  case Status::Issued:
    status = L"Issued";
    break;

  case Status::ReadyToIssue:
    status = L"ReadyToIssue";
    break;

  case Status::WaitingForDelivery:
    status = L"WaitingForDelivery";
    break;
  }

  convertor.beginBlock(className);
  convertor.field(fn::id, _id);
  convertor.field(fn::operId, std::to_wstring(_operId));
  convertor.field(fn::customerId, std::to_wstring(_customerId));
  convertor.field(fn::status, status);

  convertor.beginBlock(_products.data()->className);
  for (auto&& prod : _products)
  {
    prod.convert(convertor);
  }
  convertor.endBlock(_products.data()->className);

  convertor.endBlock(className);
}


std::wstring Order::statusToString(Status status)
{
}
