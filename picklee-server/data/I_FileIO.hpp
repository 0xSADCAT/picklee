#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <filesystem>
#include <string>
#include <tuple>
#include <vector>


/// Загрузчик данных из файлов
class I_FileIO
{
public:
  using Path = std::filesystem::path;

  struct Error
  {
    const std::wstring message;
    const std::wstring where;

    Error(const std::wstring message, const std::wstring where) : message(message), where(where)
    {
    }
  };

  template<typename T>
  struct Result
  {
    std::vector<T> results;
    std::vector<Error> errors;
  };

  I_FileIO(const Path& databaseDirectory) noexcept : _dir(databaseDirectory)
  {
  }

  virtual ~I_FileIO() noexcept = default;

  virtual Result<ProductDescription> loadDescriptions() const = 0;
  virtual Result<Operator> loadOperators() const = 0;
  virtual Result<Customer> loadCustomers() const = 0;
  virtual Result<Order> loadOrders() const = 0;
  virtual Result<Warehouse> loadWarehouses() const = 0;

  virtual void saveDescriptions(const std::vector<ProductDescription>& descriptions) const = 0;
  virtual void saveOperators(const std::vector<Operator>& operators) const = 0;
  virtual void saveCustomers(const std::vector<Customer>& customers) const = 0;
  virtual void saveOrders(const std::vector<Order>& orders) const = 0;
  virtual void saveWarehouses(const std::vector<Warehouse*>& warehouses) const = 0;

  virtual std::tuple<int, int, int> loadId() const = 0;
  virtual void saveId(int operId, int custId, int wareId) const = 0;

  inline const Path& dir() const noexcept
  {
    return _dir;
  }

protected:
  Path _dir;
};
