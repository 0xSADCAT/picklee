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
  DataBase() = default;

  AddResult addDescription(const ProductDescription& description) override;
  AddResult addOperator(const Operator& oper) override;
  AddResult addCustomer(const Customer& customer) override;
  AddResult addOrder(const Order& order) override;

  CreateResult createOperator(const Person& person) override;
  CreateResult createCustomer(const Person& person) override;
  CreateResult
  createOrder(const Operator& oper, const Customer& customer, const std::vector<ProductCount>& products) override;
  CreateResult createWarehouse(const std::wstring& description, int priority) override;

  void findOrder(const Filter& filter, VectorInserter<Order> inserter) const override;
  void findCustomer(const Filter& filter, VectorInserter<Customer> inserter) const override;
  void findOperator(const Filter& filter, VectorInserter<Operator> inserter) const override;
  void findDescription(const Filter& filter, VectorInserter<ProductDescription> inserter) const override;

  std::optional<Order> orderById(const std::wstring& id) const override;
  std::optional<Customer> customerById(int id) const override;
  std::optional<Operator> operatorById(int id) const override;
  std::optional<const Warehouse*> warehouseById(int id) const override;
  std::optional<ProductDescription> productByCode(const VendorCode& code) const override;

  void allProductCountByCode(const VendorCode& code, CountInserter inserter) const override;

  std::vector<std::pair<int, int>> canFetch(const VendorCode& code, int count, bool onlyFull) const override;

  ProductResult fetch(int warehouseId, const VendorCode& code, int count) override;
  ProductResult deliver(int warehouseId, const VendorCode& code, int count) override;

  EditResult editProductDescription(const VendorCode& code, const std::wstring& newDescription) override;
  EditResult editOperatorData(int operatorId, const Person& newData) override;
  EditResult editCustomerData(int customerId, const Person& newData) override;
  EditResult editWarehousePriority(int warehouseId, int newPriority) override;
  EditResult editWarehouseDescription(int warehouseId, const std::wstring& newDescription) override;
  EditResult setOrderStatus(const std::wstring& id, Order::Status status) override;
  EditResult addProductToOrder(const std::wstring& id, const ProductCount& product) override;

  RemoveResult removeDescription(const VendorCode& code) override;
  RemoveResult removeOperator(int id) override;
  RemoveResult removeCustomer(int id) override;
  RemoveResult removeOrder(const std::wstring& id) override;
  RemoveResult removeWarehouse(int id) override;

  void drop() override;

private:
  IdGenerator _idGenerator;                      ///< Генератор идентификаторов
  std::vector<Order> _orders;                    ///< Список заказов
  std::vector<Operator> _operators;              ///< Список операторов
  std::vector<Customer> _customers;              ///< Список заказчиков
  std::vector<Warehouse> _warehouses;            ///< Список складов
  std::vector<ProductDescription> _descriptions; ///< Список описаний
};
