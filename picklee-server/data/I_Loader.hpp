#pragma once

#include <string>
#include <vector>


class I_DataBase;


/// Загрузчик базы данных из строки
class I_Loader
{
public:
  I_Loader(I_DataBase& dataBase) : _dataBase(dataBase)
  {
  }

  virtual ~I_Loader() = default;

  /**
   * @brief Дать загрузчику строку для парсинга и загрузки данных в БД
   * @param string Строка для загрузки
   */
  virtual void convert(const std::wstring_view& string) = 0;

  /// Получить ошибки при загрузке
  virtual std::vector<std::pair<std::wstring_view, std::wstring>> errors() const = 0;

  /// Очистить лог ошибок
  virtual void clearErrors() = 0;

protected:
  I_DataBase& _dataBase;
};
