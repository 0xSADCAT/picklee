#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <filesystem>
#include <string>
#include <vector>


/// Загрузчик данных из файлов
class I_Loader
{
public:
  using File = const std::filesystem::path&;

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

  I_Loader() noexcept = default;
  virtual ~I_Loader() noexcept = default;

  virtual Result<ProductDescription> loadDescriptions(File file) const noexcept = 0;
  virtual Result<Operator> loadOperators(File file) const noexcept = 0;
  virtual Result<Customer> loadCustomers(File file) const noexcept = 0;
  virtual Result<Order> loadOrders(File file) const noexcept = 0;
  virtual Result<Warehouse> loadWarehouses(File file) const noexcept = 0;
};
