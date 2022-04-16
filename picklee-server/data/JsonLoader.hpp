#pragma once

#include "I_Loader.hpp"
#include "Person.hpp"
#include "Product.hpp"

#include <vector>


/// Загрузчик БД из формата JSON
class JsonLoader : public I_Loader
{
public:
  JsonLoader(I_DataBase& dataBase);

  void loadFrom(const std::wstring& string) override;

  std::vector<std::pair<std::wstring_view, std::wstring>> errors() const override;

  void clearErrors() override;

private:
  std::vector<std::pair<std::wstring_view, std::wstring>> _errorList;

  void pushError(std::wstring_view error, const std::wstring& string);

  bool isBracketsValid(std::wstring_view string) const;

  std::vector<ProductDescription> loadDescription(const std::wstring& string);
  std::vector<ProductCount> loadCount(const std::wstring& string);

  void loadOperator(const std::wstring& string);
  void loadCustomer(const std::wstring& string);
  void loadOrder(const std::wstring& string);
  void loadWarehouse(const std::wstring& string);
  Person loadPerson(const std::wstring& string);
};
