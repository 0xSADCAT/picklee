#pragma once

#include "I_FileIO.hpp"


class DBIO : public I_FileIO
{
public:
  DBIO(const Path& databaseDirectory);

  Result<ProductDescription> loadDescriptions() const override;
  Result<Operator> loadOperators() const override;
  Result<Customer> loadCustomers() const override;
  Result<Order> loadOrders() const override;
  Result<Warehouse> loadWarehouses() const override;

  void saveDescriptions(const std::vector<ProductDescription>& descriptions) const override;
  void saveOperators(const std::vector<Operator>& operators) const override;
  void saveCustomers(const std::vector<Customer>& customers) const override;
  void saveOrders(const std::vector<Order>& orders) const override;
  void saveWarehouses(const std::vector<Warehouse>& warehouses) const override;

  std::tuple<int, int, int> loadId() const override;
  void saveId(int operId, int custId, int wareId) const override;
};
