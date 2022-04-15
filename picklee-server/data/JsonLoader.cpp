#include "JsonLoader.hpp"

#include "../utils/Utils.hpp"
#include "Constants.hpp"
#include "I_DataBase.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <regex>


namespace
{
const static auto pushError = [](auto& container, auto&& error, auto&& string) {
  container.push_back({error, std::wstring(string)});
};
}


JsonLoader::JsonLoader(I_DataBase& dataBase) : I_Loader(dataBase)
{
}


void JsonLoader::convert(const std::wstring_view& string)
{
  if (util::str::contains(string, Warehouse::className))
  {
  }
  else if (util::str::contains(string, Operator::className))
  {
  }
  else if (util::str::contains(string, Customer::className))
  {
  }
  else if (util::str::contains(string, Order::className))
  {
  }
  else if (util::str::contains(string, ProductDescription::className))
  {
  }
  else if (util::str::contains(string, ProductCount::className))
  {
  }
  else
  {
    pushError(_errorList, err::input, string);
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
