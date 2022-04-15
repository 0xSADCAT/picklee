#pragma once

#include "I_Loader.hpp"


/// Загрузчик БД из формата JSON
class JsonLoader : public I_Loader
{
public:
  JsonLoader(I_DataBase& dataBase);

  void convert(const std::wstring_view& string) override;

  std::vector<std::pair<std::wstring_view, std::wstring>> errors() const override;

  void clearErrors() override;

private:
  std::vector<std::pair<std::wstring_view, std::wstring>> _errorList;
};
