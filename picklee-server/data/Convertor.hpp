#pragma once

#include <list>
#include <string>


/// Конвертор данных в строку
class Convertor
{
public:
  Convertor() = default;
  virtual ~Convertor() = default;

  /**
   * @brief Начать именованный блок данных
   * @param Имя блока данных
   */
  virtual void beginBlock(const std::wstring_view& blockName) = 0;

  /**
   * @brief Закончить именованный блок данных
   * @param Имя блока данных
   */
  virtual void endBlock(const std::wstring_view& blockName) = 0;

  /**
   * @brief Добавить поле с данными
   * @param Название поля данных
   * @param Данные
   */
  virtual void field(const std::wstring_view& fieldName, const std::wstring_view& fieldData) = 0;

  /**
   * @brief Собрать буфер в результирующею строку
   * @return Результирующая строка
   */
  virtual std::wstring result() = 0;

  /**
   * @brief Очистить буфер
   */
  virtual void clear() = 0;
};


/// Конвертор данных в SJON
class JsonConvertor : public Convertor
{
public:
  JsonConvertor(const std::wstring indentType = L"    ");

  virtual void beginBlock(const std::wstring_view& blockName) override;
  virtual void endBlock(const std::wstring_view&) override;

  virtual void field(const std::wstring_view& fieldName, const std::wstring_view& fieldData) override;

  virtual std::wstring result() override;
  virtual void clear() override;

private:
  int _indent = 1;
  std::wstring _indentType;

  std::list<std::wstring> _buffer;

  void addIndent();
};
