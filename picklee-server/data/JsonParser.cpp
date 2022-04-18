#include "JsonParser.hpp"

#include "../utils/Utils.hpp"
#include "Constants.hpp"
#include "I_DataBase.hpp"
#include "Order.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <regex>


namespace
{
const static auto wrapIntoFindRE = [](std::wstring_view name) noexcept {
  return LR"(\s*\{?\s*)" + std::wstring(name) + LR"(\s*\{.*)";
};


const static auto wrapParamRE = [](std::wstring_view param) noexcept {
  return L"\\s*\"" + std::wstring(param) + L"\"\\s*:\\s*\"([^\"]*)\",?\\s*";
};


const static auto wrapNodeRE = [](std::wstring_view nodeName) noexcept {
  return L"\\s*" + std::wstring(nodeName) + L"\\s*\\{\\s*(" + wrapParamRE(L".*") + L")+\\}\\s*";
};


static const auto noNewLine = [](std::wstring str) noexcept {
  for (auto& ch : str)
  {
    if (ch == L'\n')
    {
      ch = L' ';
    }
  }

  return str;
};
}


void JsonParser::parse(const std::wstring& string) noexcept
{
}


std::vector<Order> JsonParser::orders() const noexcept
{
  return _orders;
}


std::vector<Operator> JsonParser::operators() const noexcept
{
  return _operators;
}


std::vector<Customer> JsonParser::customers() const noexcept
{
  return _customers;
}


std::vector<ProductDescription> JsonParser::descriptions() const noexcept
{
  return _descriptions;
}


std::vector<Warehouse> JsonParser::warehouses() const noexcept
{
  return _warehouses;
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Order>> inserter) const noexcept
{
  for (auto&& order : _orders)
  {
    inserter = order;
  }
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Operator>> inserter) const noexcept
{
  for (auto&& oper : _operators)
  {
    inserter = oper;
  }
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Customer>> inserter) const noexcept
{
  for (auto&& cust : _customers)
  {
    inserter = cust;
  }
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<ProductDescription>> inserter) const noexcept
{
  for (auto&& desc : _descriptions)
  {
    inserter = desc;
  }
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Warehouse>> inserter) const noexcept
{
  for (auto&& ware : _warehouses)
  {
    inserter = ware;
  }
}


std::vector<std::pair<std::wstring_view, std::wstring>> JsonParser::errors() const noexcept
{
  return _errorList;
}


void JsonParser::clear() noexcept
{
  _errorList.clear();
  _orders.clear();
  _operators.clear();
  _customers.clear();
  _descriptions.clear();
  _warehouses.clear();
}


void JsonParser::pushError(std::wstring_view err, const std::wstring& string) noexcept
{
  _errorList.push_back({err, string});
}


bool JsonParser::isBrackestValid(const std::wstring& string)
{
  int count = 0;

  for (auto&& ch : string)
  {
    switch (ch)
    {
    case L'{':
      count++;
      break;

    case L'}':
      count--;
      break;

    default:
      break;
    }
  }

  return count == 0;
}


Order JsonParser::parseOrder(const std::wstring& string)
{
  const static std::wregex nodeExpr(wrapNodeRE(Order::className));
  const static std::wregex idExpr(wrapParamRE(fn::id));
  const static std::wregex operIdExpr(wrapParamRE(fn::operId));
  const static std::wregex custIdExpr(wrapParamRE(fn::customerId));
  const static std::wregex countFindRe(L"(" + wrapNodeRE(ProductCount::className) + L")");

  std::wsmatch nodeMatch;
  if (std::regex_search(string, nodeMatch, nodeExpr))
  {
    std::wstring node = nodeMatch[1].str();
    std::wsmatch idMatch;
    std::wsmatch operIdMatch;
    std::wsmatch custIdMatch;

    if (std::regex_search(node, idMatch, idExpr) and std::regex_search(node, operIdMatch, operIdExpr)
        and std::regex_search(node, custIdMatch, custIdExpr))
    {
      Order::Status status;

      return Order(
          idMatch[1].str(), std::stoi(operIdMatch[1].str()), std::stoi(custIdMatch[1].str()), parseCount(node), status);
    }
  }

  pushError(err::orderData, string);
  throw std::logic_error("Invalid Order structure");
}


Operator JsonParser::parseOperator(const std::wstring& string)
{
  const static std::wregex nodeExpr(wrapNodeRE(Operator::className));
  const static std::wregex idExpr(wrapParamRE(fn::id));
  const static std::wregex personFindRe(L"(" + wrapNodeRE(Person::className) + L")");

  std::wsmatch nodeMatch;
  if (std::regex_search(string, nodeMatch, nodeExpr))
  {
    std::wstring node = nodeMatch[1].str();
    std::wsmatch idMatch;
    std::wsmatch personMatch;

    if (std::regex_search(node, idMatch, idExpr) and std::regex_search(node, personMatch, personFindRe))
    {
      return Operator(std::stoi(idMatch[1].str()), parsePerson(personMatch[1].str()));
    }
  }

  pushError(err::operatorData, string);
  throw std::logic_error("Invalid Operator structure");
}


Customer JsonParser::parseCustomer(const std::wstring& string)
{
  // Да, этот метод почти полностью дублирует предыдущий.
  // Сделано намеренно, т.к. один из них может измениться и, скорее всего, эти изменения
  // не должны будут затронуть другой метод.

  const static std::wregex nodeExpr(wrapNodeRE(Customer::className));
  const static std::wregex idExpr(wrapParamRE(fn::id));
  const static std::wregex personFindRe(wrapIntoFindRE(Person::className));

  std::wsmatch nodeMatch;
  if (std::regex_search(string, nodeMatch, nodeExpr))
  {
    std::wstring node = nodeMatch[1].str();
    std::wsmatch idMatch;
    std::wsmatch personMatch;

    if (std::regex_search(node, idMatch, idExpr) and std::regex_search(node, personMatch, personFindRe))
    {
      return Customer(std::stoi(idMatch[1].str()), parsePerson(personMatch[1].str()));
    }
  }


  pushError(err::customerData, string);
  throw std::logic_error("Invalid Customer structure");
}


Person JsonParser::parsePerson(const std::wstring& string)
{
  const static std::wregex firstExpr(wrapParamRE(fn::firstName));
  const static std::wregex lastExpr(wrapParamRE(fn::lastName));
  const static std::wregex patronymicExpr(wrapParamRE(fn::patronymic));

  std::wsmatch first, last, patronymic;
  if (std::regex_search(string, first, firstExpr) and std::regex_search(string, last, lastExpr)
      and std::regex_search(string, patronymic, patronymicExpr))
  {
    return Person(first[1].str(), last[1].str(), patronymic[1].str());
  }

  throw std::logic_error("Invalid Person structure");
}


ProductDescription JsonParser::parseDescription(const std::wstring& string)
{
  const static std::wregex nodeExpr(wrapNodeRE(ProductDescription::className));
  const static std::wregex codeExpr(wrapParamRE(VendorCode::className));
  const static std::wregex descExpr(wrapParamRE(fn::description));

  std::wsmatch nodeMatch;
  if (std::regex_search(string, nodeMatch, nodeExpr))
  {
    std::wstring node = nodeMatch[1].str();
    std::wsmatch codeMatch;
    std::wsmatch descMatch;

    if (std::regex_search(node, codeMatch, codeExpr) and std::regex_search(node, descMatch, descExpr))
    {
      return ProductDescription(codeMatch[1].str(), descMatch[1].str());
    }
  }

  pushError(err::productDescriptionData, string);
  throw std::logic_error("Invalid ProductDescription structure");
}


std::vector<ProductCount> JsonParser::parseCount(const std::wstring& string) noexcept
{
  const static std::wregex nodeExpr(wrapNodeRE(ProductCount::className));
  const static std::wregex codeExpr(wrapParamRE(VendorCode::className));
  const static std::wregex countExpr(wrapParamRE(fn::count));

  std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), nodeExpr},
                                     std::wsregex_iterator {}};

  if (matches.empty())
  {
    pushError(err::productDescriptionData, string);
    return {};
  }

  std::vector<ProductCount> result;

  for (auto&& match : matches)
  {
    std::wstring str = match[1];
    std::wsmatch code;
    std::wsmatch desc;

    if (std::regex_search(str, code, codeExpr) and std::regex_search(str, desc, countExpr))
    {
      try
      {
        result.emplace_back(VendorCode(code[1].str()), std::stoi(desc[1].str()));
      }
      catch (...)
      {
        pushError(err::productDescriptionData, str);
        throw std::logic_error("Invalid ProductCount structure");
      }
    }
    else
    {
      pushError(err::productDescriptionData, str);
      return {};
    }
  }

  return result;
}


Warehouse JsonParser::parseWarehouse(const std::wstring& string)
{
}
