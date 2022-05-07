#include "Logger.hpp"

#include "data/DateTime.hpp"

#include <iostream>


namespace
{

void print(std::wstring_view prefix, std::wstring_view message, std::wstring_view details)
{
  std::wcout << L"[" << prefix << L"] " << DateTime::current().toString() << L":" << std::endl
             << L"\tMessage: " << message << std::endl
             << L"\tDetails: " << details << std::endl
             << std::endl;
}


void print(std::wstring_view prefix, std::wstring_view message)
{
  std::wcout << L"[" << prefix << L"] " << DateTime::current().toString() << L":" << std::endl
             << L"\tMessage: " << message << std::endl
             << std::endl;
}

}


void Logger::msg(std::wstring_view message)
{
  static constexpr std::wstring_view prefix = L"MSG";

  print(prefix, message);
}


void Logger::warn(std::wstring_view warn, std::wstring_view details)
{
  static constexpr std::wstring_view prefix = L"WARN";

  if (details.empty())
  {
    print(prefix, warn);
  }
  else
  {
    print(prefix, warn, details);
  }
}


void Logger::err(std::wstring_view err, std::wstring_view details)
{
  static constexpr std::wstring_view prefix = L"ERR";

  if (details.empty())
  {
    print(prefix, err);
  }
  else
  {
    print(prefix, err, details);
  }
}


void Logger::critical(std::wstring_view err, std::wstring_view details)
{
  static constexpr std::wstring_view prefix = L"CRITICAL";

  if (details.empty())
  {
    print(prefix, err);
  }
  else
  {
    print(prefix, err, details);
  }

  std::terminate();
}


void Logger::assertion(const char* file, int line, const char* func, const char* cond)
{
  std::wcout << "ASSERTION FAILED AT " << file << ":" << line << std::endl << func << " -> " << cond << std::endl;
  std::terminate();
}
