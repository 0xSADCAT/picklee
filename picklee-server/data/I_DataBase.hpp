#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <QList>
#include <QString>
#include <variant>


class Filter;


/**
 * Итератор для вставки в контейнер, структура:
 * Список из пар (количество продукта, идентификатор склада)
 */
using CountInserter = std::back_insert_iterator<QList<QPair<ProductCount, int>>>;


/// Результат операции добавления
enum class AddResult {
    Success,         ///< Успешно
    IdAlreadyExists, ///< Данные с таким идентификатором уже существуют
    InvalidData      ///< Некорректные данные
};


/// Результат операции создания
enum class CreateResult {
    Success,    ///< Успешно
    InvalidData ///< Некорректные данные
};


/// Результат операций поставки/отгрузки товара со склада
enum class ProductResult {
    Success,             ///< Успешно
    WarehouseIdNotFound, ///< Идентификатор склада не найден
    VendorCodeNotFound,  ///< Артикул не найден
    NotEnoughProduct,    ///< Недостаточно товара (только для отгрузки)
    InvalidCount         ///< Неверно задано количество
};


enum class EditResult {
    Success,    ///< Успешно
    IdNotFound, ///< Идентификатор не найден
    InvalidData ///< Некорректные данные
};


/// Результат операции удаления
enum class RemoveResult {
    Success,          ///< Успешно
    IdNotFound,       ///< Не найден идентификатор
    WarehouseNotEmpty ///< Склад не пустой (успешно, просто предупреждение)
};


/// Интерфейс для доступа к базе данных
class I_DataBase
{
public:
    I_DataBase() = default;
    virtual ~I_DataBase() = default;

    virtual AddResult addDescription(const ProductDescription& description) = 0;
    virtual AddResult addOperator(const Operator& oper) = 0;
    virtual AddResult addCustomer(const Customer& customer) = 0;
    virtual AddResult addOrder(const Order& order) = 0;

    virtual CreateResult createOperator(const Person& person) = 0;
    virtual CreateResult createCustomer(const Person& person) = 0;
    virtual CreateResult createOrder(const Operator& oper, const Customer& customer, 
                                     const QList<ProductCount>& products) = 0;
    virtual CreateResult createWarehouse(const QString& description, int priority) = 0;

    virtual QList<Order> findOrder(const Filter& filter) const = 0;
    virtual QList<Customer> findCustomer(const Filter& filter) const = 0;
    virtual QList<Operator> findOperator(const Filter& filter) const = 0;
    virtual QList<ProductDescription> findDescription(const Filter& filter) const = 0;

    virtual Order orderById(const QString& id) const = 0;
    virtual Customer customerById(int id) const = 0;
    virtual Operator operatorById(int id) const = 0;
    virtual const Warehouse& warehouseById(int id) const = 0;
    virtual ProductDescription productByCode(const VendorCode& code) const = 0;

    virtual void productCountByCode(const VendorCode& code, CountInserter inserter) const = 0;

    virtual QList<QPair<int, int>> canFetch(const VendorCode& code, int count) const = 0;

    virtual ProductResult fetch(int warehouseId, const VendorCode& code, int count) = 0;
    virtual ProductResult deliver(int warehouseId, const VendorCode& code, int count) = 0;

    virtual EditResult editProductDescription(const ProductDescription& newDescription) = 0;
    virtual EditResult editOperatorData(int operatorId, const Person& newData) = 0;
    virtual EditResult editCustomerData(int customerId, const Person& newData) = 0;
    virtual EditResult editWarehouseDescription(int warehouseId, const QString& newDescription) = 0;

    virtual EditResult setOrderStatus(const QString& id, Order::Status status) = 0;
    virtual EditResult addProductToOrder(const QString& id, const ProductCount& product) = 0;

    virtual RemoveResult removeDescription(const VendorCode& code) = 0;
    virtual RemoveResult removeOperator(int id) = 0;
    virtual RemoveResult removeCustomer(int id) = 0;
    virtual RemoveResult removeOrder(const QString& id) = 0;
    virtual RemoveResult removeWarehouse(int id) = 0;
};

