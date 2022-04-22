#include "Order.hpp"

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


Order::Order(const std::wstring& id,
             int operId,
             int customerId,
             const std::vector<ProductCount> products,
             Status status) noexcept
    : _id(id), _operId(operId), _customerId(customerId), _products(products), _status(status)
{
}


Order Order::fromString(std::wstring string)
{
  const static std::wregex expr(std::wstring(className)
                                + L"\\s*\\{\\s*\"([^\"]+)\"\\s*,?\\s*\"(\\d+)\"\\s*,?\\s*\"(\\d+)\"\\s*,?\\s*\"([^"
                                  L"\"]+)\"\\s*,?\\s*\\[(.*)\\]\\s*\\}");
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
    std::wstring id = match[1].str();
    int operId = std::stoi(match[2].str());
    int custId = std::stoi(match[3].str());
    std::wstring statusStr = match[4].str();
    Status status;

    if (statusStr == statusToString(Status::InProcessing))
    {
      status = Status::InProcessing;
    }
    else if (statusStr == statusToString(Status::Issued))
    {
      status = Status::Issued;
    }
    else if (statusStr == statusToString(Status::ReadyToIssue))
    {
      status = Status::ReadyToIssue;
    }
    else if (statusStr == statusToString(Status::WaitingForDelivery))
    {
      status = Status::WaitingForDelivery;
    }
    else
    {
      throw InvalidFormatException(className, string);
    }

    std::vector<ProductCount> products;
    std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), countExpr},
                                       std::wsregex_iterator {}};
    for (auto&& each : matches)
    {
      products.push_back(ProductCount::fromString(each[1].str()));
    }

    return Order(std::move(id), operId, custId, std::move(products), status);
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring Order::toString() const noexcept
{
  std::wstring result(className);

  result += L" {\n" + wrap(_id) + L", " + wrap(std::to_wstring(_operId)) + L", " + wrap(std::to_wstring(_customerId))
            + L", " + wrap(statusToString(_status)) + L",\n  [\n";

  for (auto&& prod : _products)
  {
    result += L"  " + prod.toString() + L"\n";
  }

  result += L"  ]\n}";

  return result;
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


std::wstring Order::statusToString(Status status)
{
  switch (status)
  {
  case Status::InProcessing:
    return L"InProcessing";

  case Status::WaitingForDelivery:
    return L"WaitingForDelivery";

  case Status::ReadyToIssue:
    return L"ReadyToIssue";

  case Status::Issued:
    return L"Issued";

  default:
    return L"Undefined";
  }
}
