#include "DBIO.hpp"

#include "Exceptions.hpp"

#include <fstream>
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
  return {};
}


I_FileIO::Result<Operator> DBIO::loadOperators() const
{
  return {};
}


I_FileIO::Result<Customer> DBIO::loadCustomers() const
{
  return {};
}


I_FileIO::Result<Order> DBIO::loadOrders() const
{
  return {};
}


I_FileIO::Result<Warehouse> DBIO::loadWarehouses() const
{
  return {};
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
