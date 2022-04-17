#include "Product.hpp"

#include "Constants.hpp"
#include "Convertor.hpp"


using namespace std::string_literals;


VendorCode::VendorCode(const std::wstring& code) noexcept : _str(code)
{
}


std::wstring VendorCode::str() const noexcept
{
  return _str;
}


bool operator==(const VendorCode& left, const VendorCode& right) noexcept
{
  return left.str() == right.str();
}


bool operator!=(const VendorCode& left, const VendorCode& right) noexcept
{
  return left.str() != right.str();
}


ProductDescription::ProductDescription(const VendorCode& code, const std::wstring& description) noexcept
    : _code(code), _description(description)
{
}


const VendorCode& ProductDescription::code() const noexcept
{
  return _code;
}


void ProductDescription::setCode(const VendorCode& newCode) noexcept
{
  _code = newCode;
}


const std::wstring& ProductDescription::description() const noexcept
{
  return _description;
}


void ProductDescription::setDescription(const std::wstring& newDescription) noexcept
{
  _description = newDescription;
}


void ProductDescription::convert(Convertor& convertor) const noexcept
{
  convertor.beginBlock(className);
  convertor.field(VendorCode::className, _code.str());
  convertor.field(fn::description, _description);
  convertor.endBlock(className);
}


ProductCount::ProductCount(const VendorCode& code, int count) noexcept : _code(code), _count(count)
{
}


const VendorCode& ProductCount::code() const noexcept
{
  return _code;
}


void ProductCount::setCode(const VendorCode& newCode) noexcept
{
  _code = newCode;
}


int ProductCount::count() const noexcept
{
  return _count;
}


void ProductCount::setCount(int newCount) noexcept
{
  _count = newCount;
}


int& ProductCount::countRef() noexcept
{
  return _count;
}


void ProductCount::convert(Convertor& convertor) const noexcept
{
  convertor.beginBlock(className);
  convertor.field(VendorCode::className, _code.str());
  convertor.field(fn::count, std::to_wstring(_count));
  convertor.endBlock(className);
}
