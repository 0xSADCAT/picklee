#pragma once

#include <string>
#include <vector>


class I_DataBase;


/// Загрузчик базы данных из строки
class I_Loader
{
public:
  I_Loader(I_DataBase& dataBase) noexcept : _dataBase(dataBase)
  {
  }

  virtual ~I_Loader() noexcept = default;

  /**
   * @brief Загрузить в БД из строки
   * @param string Строка для загрузки
   */
  virtual void loadFrom(const std::wstring& string) noexcept = 0;

  /// Получить ошибки при загрузке
  virtual std::vector<std::pair<std::wstring_view, std::wstring>> errors() const noexcept = 0;

  /// Очистить лог ошибок
  virtual void clearErrors() noexcept = 0;

protected:
  I_DataBase& _dataBase;
};
