#include "DBIO.hpp"

#include "Exceptions.hpp"

#include <fstream>
#include <regex>
#include <string>


namespace
{

struct FileName
{
  const static inline std::string dir = "picklee-database";
  const static inline std::string suffix = ".pf";
  const static inline std::string configs = "picklee-configs" + suffix;
  const static inline std::string desc = "descriptions" + suffix;
  const static inline std::string oper = "operators" + suffix;
  const static inline std::string cust = "customers" + suffix;
  const static inline std::string order = "orders" + suffix;
  const static inline std::string ware = "warehouses" + suffix;
};


std::string path(const std::filesystem::path& dir, const std::string& name)
{
  const static std::string sep = "/";
  if (dir.string().back() != '/')
  {
    return dir.string() + sep + FileName::dir + sep + name;
  }
  return dir.string() + FileName::dir + sep + name;
}

}


DBIO::DBIO(const Path& databaseDirectory) : I_FileIO(databaseDirectory)
{
  if (not std::filesystem::exists(databaseDirectory.string() + '/' + FileName::dir))
  {
    if (not std::filesystem::create_directories(databaseDirectory.string() + '/' + FileName::dir))
    {
      throw FileIOException(databaseDirectory.string());
    }
  }
}


I_FileIO::Result<ProductDescription> DBIO::loadDescriptions() const
{
  Result<ProductDescription> result;

  std::wifstream stream(path(_dir, FileName::desc));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring buffer;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      try
      {
        result.results.push_back(ProductDescription::fromString(buffer));
      }
      catch (const InvalidFormatException& ex)
      {
        result.errors.push_back({ex.error(), ex.where()});
      }
      catch (const std::invalid_argument&)
      {
        result.errors.push_back({L"Invalid number format", buffer});
      }
    }
  }

  return result;
}


I_FileIO::Result<Operator> DBIO::loadOperators() const
{
  Result<Operator> result;

  std::wifstream stream(path(_dir, FileName::oper));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring buffer;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      try
      {
        result.results.push_back(Operator::fromString(buffer));
      }
      catch (const InvalidFormatException& ex)
      {
        result.errors.push_back({ex.error(), ex.where()});
      }
      catch (const std::invalid_argument&)
      {
        result.errors.push_back({L"Invalid number format", buffer});
      }
    }
  }

  return result;
}


I_FileIO::Result<Customer> DBIO::loadCustomers() const
{
  Result<Customer> result;

  std::wifstream stream(path(_dir, FileName::cust));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring buffer;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      try
      {
        result.results.push_back(Customer::fromString(buffer));
      }
      catch (const InvalidFormatException& ex)
      {
        result.errors.push_back({ex.error(), ex.where()});
      }
      catch (const std::invalid_argument&)
      {
        result.errors.push_back({L"Invalid number format", buffer});
      }
    }
  }

  return result;
}


I_FileIO::Result<Order> DBIO::loadOrders() const
{
  const static std::wregex expr {L"(\\s*" + std::wstring(Order::className) + LR"(\s*\{[^\[]+\[[^\[]*\]\s*\}))"};

  Result<Order> result;

  std::wifstream stream(path(_dir, FileName::order));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring string;
  std::wstring buffer;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      if (buffer.back() == L'\n')
      {
        buffer.back() = L' ';
      }

      string += buffer;
    }
  }

  std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), expr},
                                     std::wsregex_iterator {}};
  for (auto&& match : matches)
  {
    try
    {
      result.results.push_back(Order::fromString(match[1].str()));
    }
    catch (const InvalidFormatException& ex)
    {
      result.errors.push_back({ex.error(), ex.where()});
    }
    catch (const std::invalid_argument&)
    {
      result.errors.push_back({L"Invalid number format", buffer});
    }
  }

  return result;
}


I_FileIO::Result<Warehouse> DBIO::loadWarehouses() const
{
  const static std::wregex expr {L"(\\s*" + std::wstring(Warehouse::className) + LR"(\s*\{[^\[]+\[[^\[]*\]\s*\}))"};

  Result<Warehouse> result;

  std::wifstream stream(path(_dir, FileName::ware));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring string;
  std::wstring buffer;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      if (buffer.back() == L'\n')
      {
        buffer.back() = L' ';
      }

      string += buffer;
    }
  }

  std::vector<std::wsmatch> matches {std::wsregex_iterator {string.begin(), string.end(), expr},
                                     std::wsregex_iterator {}};
  for (auto&& match : matches)
  {
    try
    {
      result.results.push_back(Warehouse::fromString(match[1].str()));
    }
    catch (const InvalidFormatException& ex)
    {
      result.errors.push_back({ex.error(), ex.where()});
    }
    catch (const std::invalid_argument&)
    {
      result.errors.push_back({L"Invalid number format", buffer});
    }
  }

  return result;
}


void DBIO::saveDescriptions(const std::vector<ProductDescription>& descriptions) const
{
  std::wofstream stream(path(_dir, FileName::desc));

  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  for (auto&& desc : descriptions)
  {
    stream << desc.toString() << L'\n';
  }

  stream.close();
}


void DBIO::saveOperators(const std::vector<Operator>& operators) const
{
  std::wofstream stream(path(_dir, FileName::oper));

  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  for (auto&& desc : operators)
  {
    stream << desc.toString() << L'\n';
  }

  stream.close();
}


void DBIO::saveCustomers(const std::vector<Customer>& customers) const
{
  std::wofstream stream(path(_dir, FileName::cust));

  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  for (auto&& desc : customers)
  {
    stream << desc.toString() << L'\n';
  }

  stream.close();
}


void DBIO::saveOrders(const std::vector<Order>& orders) const
{
  std::wofstream stream(path(_dir, FileName::order));

  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  for (auto&& desc : orders)
  {
    stream << desc.toString() << L'\n';
  }

  stream.close();
}


void DBIO::saveWarehouses(const std::vector<Warehouse>& warehouses) const
{
  std::wofstream stream(path(_dir, FileName::ware));

  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  for (auto&& desc : warehouses)
  {
    stream << desc.toString() << L'\n';
  }

  stream.close();
}


std::tuple<int, int, int> DBIO::loadId() const
{
  const static std::wregex expr {LR"(Id \{\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\})"};

  std::wifstream stream(path(_dir, FileName::configs));
  if (not stream.is_open())
  {
    throw FileIOException(_dir);
  }

  std::wstring buffer;
  std::wsmatch match;
  while (std::getline(stream, buffer))
  {
    if (not buffer.empty())
    {
      if (std::regex_search(buffer, match, expr))
      {
        return {std::stoi(match[1].str()), std::stoi(match[2].str()), std::stoi(match[3].str())};
      }
    }
  }

  throw FileIOException(path(_dir, FileName::configs));
}


void DBIO::saveId(int operId, int custId, int wareId) const
{
  std::wofstream stream(path(_dir, FileName::configs));

  if (not stream.is_open())
  {
    throw FileIOException(path(_dir, FileName::configs));
  }

  stream << L"Id { " << std::to_wstring(operId) << L", " << std::to_wstring(custId) << L", " << std::to_wstring(wareId)
         << L" }";

  stream.close();
}
