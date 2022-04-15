#pragma once

#include <algorithm>
#include <string>


#define function static const auto


/// Работа со строками
namespace util::str
{
/// Содержит ли строка str подстроку substr
function contains = [](const std::wstring_view& str, const std::wstring_view& substr) {
  return str.find(substr) != str.npos;
};


/// Начинается ли строка str с префикса prefix
function startsWith = [](const std::wstring_view& str, const std::wstring_view& prefix) {
  if (str.length() < prefix.length())
    return false;
  return std::equal(str.begin(), str.begin() + prefix.length(), prefix.begin());
};


/// Оканчивается ли строка str суффиксом suffix
function endsWith = [](const std::wstring_view& str, const std::wstring_view& suffix) {
  if (str.length() < suffix.length())
    return false;
  return std::equal(str.begin() + str.length() - suffix.length(), str.end(), suffix.begin(), suffix.end());
};

} // util::str


/// Работа с контейнерами
namespace util::container
{

/// Содержитли контейнер container элемент element
function contains = [](const auto&& container, const auto&& element) {
  return std::find(container.begin(), container.end(), element) != container.end();
};
} // util::container


#undef function
