#pragma once

#include <string>


class Convertor;


/// Артикул
class VendorCode
{
public:
  static inline const std::wstring className = L"VendorCode";

  VendorCode(const std::wstring& code) noexcept;

  std::wstring str() const noexcept;

private:
  std::wstring _str;
};


bool operator==(const VendorCode& left, const VendorCode& right) noexcept;
bool operator!=(const VendorCode& left, const VendorCode& right) noexcept;


/// Пара артикул-описание
class ProductDescription
{
public:
  static inline const std::wstring className = L"ProductDescription";

  ProductDescription(const VendorCode& code, const std::wstring& description) noexcept;

  const VendorCode& code() const noexcept;
  void setCode(const VendorCode& newCode) noexcept;

  const std::wstring& description() const noexcept;
  void setDescription(const std::wstring& newDescription) noexcept;

  void convert(Convertor& convertor) const noexcept;

private:
  VendorCode _code;
  std::wstring _description;
};


/// Пара артикул-количество
class ProductCount
{
public:
  static inline const std::wstring className = L"ProductCount";

  ProductCount(const VendorCode& code, int count) noexcept;

  const VendorCode& code() const noexcept;
  void setCode(const VendorCode& newCode) noexcept;

  int count() const noexcept;
  void setCount(int newCount) noexcept;

  int& countRef() noexcept;

  void convert(Convertor& convertor) const noexcept;

private:
  VendorCode _code;
  int _count;
};
