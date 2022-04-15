#include "Convertor.hpp"

#include <cassert>


using namespace std::string_literals;


JsonConvertor::JsonConvertor(const std::wstring indentType) : _indentType(indentType)
{
  _buffer.push_back(L"{\n");
}


void JsonConvertor::beginBlock(const std::wstring_view& blockName)
{
  addIndent();
  ++_indent;

  _buffer.emplace_back(blockName);
  _buffer.emplace_back(L" {\n");
}


void JsonConvertor::endBlock(const std::wstring_view&)
{
  assert(_indent > 1);

  --_indent;
  addIndent();
  _buffer.push_back(L"}\n");
}


void JsonConvertor::field(const std::wstring_view& fieldName, const std::wstring_view& fieldData)
{
  addIndent();
  _buffer.push_back(L"\"");
  _buffer.emplace_back(fieldName);
  _buffer.emplace_back(L"\": \"");
  _buffer.emplace_back(fieldData);
  _buffer.emplace_back(L"\",\n");
}


std::wstring JsonConvertor::result()
{
  std::wstring result;

  for (auto&& str : _buffer)
  {
    result += str;
  }

  result += L"}\n";

  return result;
}


void JsonConvertor::clear()
{
  _buffer.clear();
  _buffer.push_back(L"{\n");
  _indent = 1;
}


void JsonConvertor::addIndent()
{
  for (int i = 0; i < _indent; ++i)
  {
    _buffer.push_back(_indentType);
  }
}
