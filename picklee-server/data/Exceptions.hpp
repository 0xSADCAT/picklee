#pragma once

#include <exception>
#include <string>


class InvalidFormatException : public std::exception
{
public:
  InvalidFormatException(std::wstring_view error, const std::wstring& where) : _error(error), _where(where)
  {
  }

  const std::wstring& error() const
  {
    return _error;
  }

  const std::wstring& where() const
  {
    return _where;
  }

private:
  const std::wstring _error;
  const std::wstring _where;
};


class FileIOException : public std::exception
{
public:
  FileIOException(const std::string& path) : _path(path)
  {
  }

  std::string path() const noexcept
  {
    return _path;
  }

  const char* what() const noexcept override
  {
    return _path.c_str();
  }

private:
  const std::string _path;
};
