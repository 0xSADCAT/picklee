#pragma once

#include "I_Loader.hpp"
#include "Person.hpp"
#include "Product.hpp"

#include <vector>


/// Загрузчик БД из формата JSON
class JsonLoader : public I_Loader
{
public:
  JsonLoader(I_DataBase& dataBase) noexcept;

  void loadFrom(const std::wstring& string) noexcept override;

  std::vector<std::pair<std::wstring_view, std::wstring>> errors() const noexcept override;

  void clearErrors() noexcept override;

private:
  std::vector<std::pair<std::wstring_view, std::wstring>> _errorList;

  void pushError(std::wstring_view error, const std::wstring& string) noexcept;

  bool isBracketsValid(std::wstring_view string) const noexcept;

  std::vector<ProductDescription> loadDescription(const std::wstring& string) noexcept;
  std::vector<ProductCount> loadCount(const std::wstring& string) noexcept;

  void loadOperator(const std::wstring& string) noexcept;
  void loadCustomer(const std::wstring& string) noexcept;
  void loadOrder(const std::wstring& string) noexcept;
  void loadWarehouse(const std::wstring& string) noexcept;
  Person loadPerson(const std::wstring& string);
};
