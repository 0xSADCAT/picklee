#pragma once

#include "I_DataBase.hpp"
#include "IdGenerator.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <string>
#include <vector>


template<typename T>
using VectorInserter = std::back_insert_iterator<std::vector<T>>;


class DataBase : public I_DataBase
{
public:
  DataBase() noexcept = default;

  AddResult addDescription(const ProductDescription& description) noexcept override;
  AddResult addOperator(const Operator& oper) noexcept override;
  AddResult addCustomer(const Customer& customer) noexcept override;
  AddResult addOrder(const Order& order) noexcept override;
  AddResult addWarehouse(const Warehouse& warehouse) noexcept override;

  CreateResult createOperator(const Person& person) noexcept override;
  CreateResult createCustomer(const Person& person) noexcept override;
  CreateResult createOrder(const Operator& oper,
                           const Customer& customer,
                           const std::vector<ProductCount>& products) noexcept override;
  CreateResult createWarehouse(const std::wstring& description, int priority) noexcept override;

  void findOrder(const Filter& filter, VectorInserter<Order> inserter) const noexcept override;
  void findCustomer(const Filter& filter, VectorInserter<Customer> inserter) const noexcept override;
  void findOperator(const Filter& filter, VectorInserter<Operator> inserter) const noexcept override;
  void findDescription(const Filter& filter, VectorInserter<ProductDescription> inserter) const noexcept override;

  std::optional<Order> orderById(const std::wstring& id) const noexcept override;
  std::optional<Customer> customerById(int id) const noexcept override;
  std::optional<Operator> operatorById(int id) const noexcept override;
  std::optional<const Warehouse*> warehouseById(int id) const noexcept override;
  std::optional<ProductDescription> productByCode(const VendorCode& code) const noexcept override;

  void allProductCountByCode(const VendorCode& code, CountInserter inserter) const noexcept override;

  const std::vector<Warehouse*> warehouses() const noexcept override;

  std::tuple<int, int, int> ids() const noexcept override;

  void resetId(int oper, int cust, int warehouse) noexcept override;

  std::vector<std::pair<int, int>> canFetch(const VendorCode& code, int count, bool onlyFull) const noexcept override;

  ProductResult fetch(int warehouseId, const VendorCode& code, int count) noexcept override;
  ProductResult deliver(int warehouseId, const VendorCode& code, int count) noexcept override;

  EditResult editProductDescription(const VendorCode& code, const std::wstring& newDescription) noexcept override;
  EditResult editOperatorData(int operatorId, const Person& newData) noexcept override;
  EditResult editCustomerData(int customerId, const Person& newData) noexcept override;
  EditResult editWarehousePriority(int warehouseId, int newPriority) noexcept override;
  EditResult editWarehouseDescription(int warehouseId, const std::wstring& newDescription) noexcept override;
  EditResult setOrderStatus(const std::wstring& id, Order::Status status) noexcept override;
  EditResult addProductToOrder(const std::wstring& id, const ProductCount& product) noexcept override;

  RemoveResult removeDescription(const VendorCode& code) noexcept override;
  RemoveResult removeOperator(int id) noexcept override;
  RemoveResult removeCustomer(int id) noexcept override;
  RemoveResult removeOrder(const std::wstring& id) noexcept override;
  RemoveResult removeWarehouse(int id) noexcept override;

  void drop() noexcept override;

private:
  IdGenerator _idGenerator;                      ///< Генератор идентификаторов
  std::vector<Order> _orders;                    ///< Список заказов
  std::vector<Operator> _operators;              ///< Список операторов
  std::vector<Customer> _customers;              ///< Список заказчиков
  std::vector<Warehouse> _warehouses;            ///< Список складов
  std::vector<ProductDescription> _descriptions; ///< Список описаний
};
