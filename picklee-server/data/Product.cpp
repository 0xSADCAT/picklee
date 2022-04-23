#include "Product.hpp"

#include "Exceptions.hpp"

#include <regex>


using namespace std::string_literals;


namespace
{

const static auto wrap = [](const std::wstring& str) {
  return L"\"" + str + L"\"";
};

}


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


ProductDescription ProductDescription::fromString(const std::wstring& string)
{
  const static std::wregex expr(std::wstring(className) + L"\\s*\\{\\s*\"([^\"]+)\"\\s*,?\\s*\"([^\"]+)\"\\s*\\}\\s*");

  std::wsmatch match;
  if (std::regex_search(string, match, expr))
  {
    return ProductDescription(match[1].str(), match[2].str());
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring ProductDescription::toString() const noexcept
{
  return std::wstring(className) + L" { " + wrap(_code.str()) + L", " + wrap(_description) + L" } ";
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


ProductCount::ProductCount(const VendorCode& code, int count) noexcept : _code(code), _count(count)
{
}


ProductCount ProductCount::fromString(const std::wstring& string)
{
  const static std::wregex expr(ProductCount::expr);
  std::wsmatch match;
  if (std::regex_search(string, match, expr))
  {
    return ProductCount(match[1].str(), std::stoi(match[2].str()));
  }
  else
  {
    throw InvalidFormatException(className, string);
  }
}


std::wstring ProductCount::toString() const noexcept
{
  return std::wstring(className) + L" { " + wrap(_code.str()) + L", " + wrap(std::to_wstring(_count)) + L" } ";
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
