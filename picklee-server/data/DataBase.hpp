#pragma once

#include "I_DataBase.hpp"
#include "IdGenerator.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <QString>
#include <vector>


class DataBase : public I_DataBase
{
public:
    DataBase() = default;

    virtual AddResult addDescription(const VendorCode& code, const ProductDescription& description) override;
    virtual AddResult addOperator(const Operator& oper) override;
    virtual AddResult addCustomer(const Customer& customer) override;
    virtual AddResult addOrder(const Order& order) override;

    virtual CreateResult createOperator(const Person& person) override;
    virtual CreateResult createCustomer(const Person& person) override;
    virtual CreateResult createOrder(const Operator& oper, const Customer& customer, const std::vector<ProductCount>& products) override;
    virtual CreateResult createWarehouse(const QString& description, int priority) override;

    virtual void findOrder(const Filter& filter, std::back_insert_iterator<std::vector<Order>> inserter) const override;
    virtual void findCustomer(const Filter& filter, std::back_insert_iterator<std::vector<Customer>> inserter) const override;
    virtual void findOperator(const Filter& filter, std::back_insert_iterator<std::vector<Operator>> inserter) const override;
    virtual void findDescription(const Filter& filter, std::back_insert_iterator<std::vector<ProductDescription>> inserter) const override;

    virtual std::optional<Order> orderById(const QString& id) const override;
    virtual std::optional<Customer> customerById(int id) const override;
    virtual std::optional<Operator> operatorById(int id) const override;
    virtual std::optional<const Warehouse*> warehouseById(int id) const override;
    virtual std::optional<ProductDescription> productByCode(const VendorCode& code) const override;

    virtual void allProductCountByCode(const VendorCode& code, CountInserter inserter) const override;

    virtual std::vector<std::pair<int, int>> canFetch(const VendorCode& code, int count, bool onlyFull) const override;

    virtual ProductResult fetch(int warehouseId, const VendorCode& code, int count) override;
    virtual ProductResult deliver(int warehouseId, const VendorCode& code, int count) override;

    virtual EditResult editProductDescription(const VendorCode& code, const QString& newDescription) override;
    virtual EditResult editOperatorData(int operatorId, const Person& newData) override;
    virtual EditResult editCustomerData(int customerId, const Person& newData) override;
    virtual EditResult editWarehousePriority(int warehouseId, int newPriority) override;
    virtual EditResult editWarehouseDescription(int warehouseId, const QString& newDescription) override;
    virtual EditResult setOrderStatus(const QString& id, Order::Status status) override;
    virtual EditResult addProductToOrder(const QString& id, const ProductCount& product) override;

    virtual RemoveResult removeDescription(const VendorCode& code) override;
    virtual RemoveResult removeOperator(int id) override;
    virtual RemoveResult removeCustomer(int id) override;
    virtual RemoveResult removeOrder(const QString& id) override;
    virtual RemoveResult removeWarehouse(int id) override;

private:
    IdGenerator _idGenerator;                      ///< Генератор идентификаторов
    std::vector<Order> _orders;                    ///< Список заказов
    std::vector<Operator> _operators;              ///< Список операторов
    std::vector<Customer> _customers;              ///< Список заказчиков
    std::vector<Warehouse> _warehouses;            ///< Список складов
    std::vector<ProductDescription> _descriptions; ///< Список описаний
};
