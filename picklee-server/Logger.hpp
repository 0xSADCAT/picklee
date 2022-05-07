#pragma once

#include <string_view>


#define PICKLEE_ASSERT(cond)                                           \
  if (not (cond))                                                      \
  {                                                                    \
    Logger::assertion(__FILE__, __LINE__, __PRETTY_FUNCTION__, #cond); \
  }


namespace Logger
{

void msg(std::wstring_view message);
void warn(std::wstring_view warn, std::wstring_view details = L"");
void err(std::wstring_view err, std::wstring_view details = L"");
void critical(std::wstring_view err, std::wstring_view details = L"");

void assertion(const char* file, int line, const char* func, const char* cond);

}
