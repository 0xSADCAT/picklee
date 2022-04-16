#include "JsonLoader.hpp"

#include "../utils/Utils.hpp"
#include "Constants.hpp"
#include "I_DataBase.hpp"
#include "Order.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <regex>


namespace
{
const static auto wrapIntoFindRE = [](std::wstring_view name) {
  return LR"(\s*\{?\s*)" + std::wstring(name) + LR"(\s*\{.*)";
};


const static auto wrapParamRE = [](std::wstring_view param) {
  return L"\\s*\"" + std::wstring(param) + L"\"\\s*:\\s*\"([^\"]*)\",?\\s*";
};


const static auto wrapNodeRE = [](std::wstring_view nodeName) {
  return L"\\s*" + std::wstring(nodeName) + L"\\s*\\{\\s*(" + wrapParamRE(L".*") + L")+\\}\\s*";
};


static const auto noNewLine = [](std::wstring str) {
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


JsonLoader::JsonLoader(I_DataBase& dataBase) : I_Loader(dataBase)
{
}


void JsonLoader::loadFrom(const std::wstring& string)
{
  // TODO: Надо переработать, чтобы метод кушал все подряд

  const static std::wregex operatorFindRe(wrapIntoFindRE(Operator::className));
  const static std::wregex customerFindRe(wrapIntoFindRE(Customer::className));
  const static std::wregex orderFindRe(wrapIntoFindRE(Order::className));
  const static std::wregex warehouseFindRe(wrapIntoFindRE(Warehouse::className));

  const static std::wregex descriptionFindRe(wrapIntoFindRE(ProductDescription::className));

  if (not isBracketsValid(string))
  {
    pushError(err::input, string);
    return;
  }

  std::wstring noNewLineString = noNewLine(string);

  if (std::regex_match(noNewLineString, operatorFindRe))
  {
    loadOperator(noNewLineString);
  }
  else if (std::regex_match(noNewLineString, customerFindRe))
  {
    loadCustomer(noNewLineString);
  }
  else if (std::regex_match(noNewLineString, orderFindRe))
  {
    loadOrder(noNewLineString);
  }
  else if (std::regex_match(noNewLineString, warehouseFindRe))
  {
    loadWarehouse(noNewLineString);
  }
  else if (std::regex_match(noNewLineString, descriptionFindRe))
  {
    auto data = loadDescription(noNewLineString);
    for (auto&& each : data)
    {
      _dataBase.addDescription(std::move(each));
    }
  }
  else
  {
    pushError(err::input, string);
  }
}


std::vector<std::pair<std::wstring_view, std::wstring> > JsonLoader::errors() const
{
  return _errorList;
}


void JsonLoader::clearErrors()
{
  _errorList.clear();
}


void JsonLoader::pushError(std::wstring_view error, const std::wstring& string)
{
  _errorList.push_back({error, string});
}


bool JsonLoader::isBracketsValid(std::wstring_view string) const
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


std::vector<ProductDescription> JsonLoader::loadDescription(const std::wstring& string)
{
  const static std::wregex nodeExpr(wrapNodeRE(ProductDescription::className));
  const static std::wregex codeExpr(wrapParamRE(VendorCode::className));
  const static std::wregex descExpr(wrapParamRE(fn::description));

  std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), nodeExpr},
                                     std::wsregex_iterator {}};

  if (matches.empty())
  {
    pushError(err::productDescriptionData, string);
    return {};
  }

  std::vector<ProductDescription> result;

  for (auto&& match : matches)
  {
    std::wstring str = match[1];
    std::wsmatch code;
    std::wsmatch desc;

    if (std::regex_search(str, code, codeExpr) and std::regex_search(str, desc, descExpr))
    {
      result.emplace_back(VendorCode(code[1].str()), desc[1].str());
    }
    else
    {
      pushError(err::productDescriptionData, str);
    }
  }

  return result;
}


std::vector<ProductCount> JsonLoader::loadCount(const std::wstring& string)
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
      }
    }
    else
    {
      pushError(err::productDescriptionData, str);
    }
  }

  return result;
}


void JsonLoader::loadOperator(const std::wstring& string)
{
  const static std::wregex nodeExpr(wrapNodeRE(Operator::className));
  const static std::wregex idExpr(wrapParamRE(fn::id));
  const static std::wregex personFindRe(L"(" + wrapNodeRE(Person::className) + L")");

  std::vector<std::wsmatch> matches
      = {std::wsregex_iterator {string.cbegin(), string.cend(), nodeExpr}, std::wsregex_iterator {}};

  if (matches.empty())
  {
    pushError(err::operatorData, string);
    return;
  }

  for (auto&& match : matches)
  {
    std::wstring res = match[1].str();
    std::wsmatch matchId;

    try
    {
      if (std::regex_search(res, matchId, idExpr))
      {
        _dataBase.addOperator(Operator(std::stoi(matchId[1].str()), loadPerson(res)));
      }
    }
    catch (...)
    {
      pushError(err::operatorData, res);
    }
  }
}


void JsonLoader::loadCustomer(const std::wstring& string)
{
  // Да, этот метод почти полностью дублирует предыдущий.
  // Сделано намеренно, т.к. один из них может измениться и, скорее всего, эти изменения
  // не должны будут затронуть другой метод.

  const static std::wregex nodeExpr(wrapNodeRE(Customer::className));
  const static std::wregex idExpr(wrapParamRE(fn::id));
  const static std::wregex personFindRe(wrapIntoFindRE(Person::className));

  std::vector<std::wsmatch> matches {std::wsregex_iterator {string.cbegin(), string.cend(), nodeExpr},
                                     std::wsregex_iterator {}};

  if (matches.empty())
  {
    pushError(err::customerData, string);
    return;
  }

  for (auto&& match : matches)
  {
    std::wstring res = match[1].str();
    std::wsmatch matchId;

    try
    {
      if (std::regex_search(res, matchId, idExpr))
      {
        _dataBase.addCustomer(Customer(std::stoi(matchId[1].str()), loadPerson(res)));
      }
    }
    catch (...)
    {
      pushError(err::operatorData, res);
    }
  }
}


void JsonLoader::loadOrder(const std::wstring& string)
{
}


void JsonLoader::loadWarehouse(const std::wstring& string)
{
}


Person JsonLoader::loadPerson(const std::wstring& string)
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
  else
  {
    throw std::logic_error("Invalid person structure");
  }
}
