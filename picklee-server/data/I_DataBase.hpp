#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <QString>
#include <optional>
#include <vector>


class Filter;


/**
 * Итератор для вставки в контейнер, структура:
 * Список из пар (количество продукта, идентификатор склада)
 */
using CountInserter = std::back_insert_iterator<std::vector<std::pair<ProductCount, int>>>;


/// Результат операции добавления
enum class AddResult {
    Success,         ///< Успешно
    IdAlreadyExists, ///< Данные с таким идентификатором уже существуют
    InvalidData      ///< Некорректные данные
};


/// Результат операции создания
struct CreateResult {
    enum class Status {
        Success,    ///< Успешно
        InvalidData ///< Некорректные данные
    };

    const Status status;                                 ///< Статус операции
    const std::variant<QString, int, std::monostate> id; ///< Идентификатор, если создание было успешным

    CreateResult(Status status, int id)
        : status(status),
          id(id)
    {
    }

    CreateResult(Status status, const QString& id)
        : status(status),
          id(id)
    {
    }

    CreateResult(Status status)
        : status(status),
          id()
    {
    }
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

    /// Добавить описание
    virtual AddResult addDescription(const VendorCode& code, const ProductDescription& description) = 0;
    /// Добавить оператора
    virtual AddResult addOperator(const Operator& oper) = 0;
    /// Добавить заказчика
    virtual AddResult addCustomer(const Customer& customer) = 0;
    /// Добавить заказ
    virtual AddResult addOrder(const Order& order) = 0;

    /// Создать ногово оператора
    virtual CreateResult createOperator(const Person& person) = 0;
    /// Создать нового заказчика
    virtual CreateResult createCustomer(const Person& person) = 0;
    /// Создать ногый заказ
    virtual CreateResult createOrder(const Operator& oper, const Customer& customer, const std::vector<ProductCount>& products) = 0;
    /// Создать новый склад
    virtual CreateResult createWarehouse(const QString& description, int priority) = 0;

    /// Найти заказы по фильтру
    virtual std::vector<Order> findOrder(const Filter& filter) const = 0;
    /// Найти заказчиков по фильтру
    virtual std::vector<Customer> findCustomer(const Filter& filter) const = 0;
    /// Найти операторов по фильтру
    virtual std::vector<Operator> findOperator(const Filter& filter) const = 0;
    /// Найти описания по фильтру
    virtual std::vector<ProductDescription> findDescription(const Filter& filter) const = 0;

    /// Найти конктерный заказ по идентификатору
    virtual std::optional<Order> orderById(const QString& id) const = 0;
    /// Найти конктерного заказчика по идентификатору
    virtual std::optional<Customer> customerById(int id) const = 0;
    /// Найти конктерного оператора по идентификатору
    virtual std::optional<Operator> operatorById(int id) const = 0;
    /// Найти конктерный склад по идентификатору
    virtual std::optional<const Warehouse*> warehouseById(int id) const = 0;
    /// Найти конктерное описание по артикулу
    virtual std::optional<ProductDescription> productByCode(const VendorCode& code) const = 0;

    /**
     * @brief Собрать в итератор все продукты по артикулу
     * @param code Артикул для поиска
     * @param inserter Итератор вставки в конец результирующего контейнера
     *
     * @details Операция вставляет в контейнер по переданному итератору вставки в конец все пары артикул-количество
     *          и идентификатор склада, на котором этот продукт был обнаружен.
     *          Например, если есть 2 склада с артикулом #ar: id = 3, количество = 2 и id = 34, количество = 1, в таком
     *          случае функция вернет следующее:
     *          { {{#ar, 3},  2},
     *            {{#ar, 34}, 1} }
     */
    virtual void allProductCountByCode(const VendorCode& code, CountInserter inserter) const = 0;

    /**
     * @brief Можно ли получить товар (с любого склада)
     * @param code Артикул товара
     * @param count Количество
     * @param onlyFull Если выставить true, то склады, где товар есть, но его количество меньше @c count не будут
     *                 включены в результирующий список
     * @return Список пар {id склада, количество}
     *
     * @note Под количеством в возвращаемом значении подразумевается, что если хотим получить 5 штук, а на складе только
     *       3, то второй элемент пары будет равен 3.
     *       Функция собирает данные со складов, исключая те, на которых товара нет вообще.
     */
    virtual std::vector<std::pair<int, int>> canFetch(const VendorCode& code, int count, bool onlyFull) const = 0;

    /**
     * @brief Получить товар со склада
     * @param warehouseId Идентификатор склада
     * @param code Артикул товара
     * @param count Количество для получения
     * @return Результат операции
     */
    virtual ProductResult fetch(int warehouseId, const VendorCode& code, int count) = 0;

    /**
     * @brief Поставить товар на склад
     * @param warehouseId Идентификатор склада
     * @param code Артикул товара
     * @param count Количество для поставки
     * @return Результат операции
     */
    virtual ProductResult deliver(int warehouseId, const VendorCode& code, int count) = 0;

    /**
     * @brief Редактировать описание продукта
     * @param code Артикул товара
     * @param newDescription Новое описание товара
     * @return Результат операции
     */
    virtual EditResult editProductDescription(const VendorCode& code, const ProductDescription& newDescription) = 0;

    /**
     * @brief Редактировать данные об операторе
     * @param operatorId Идентификатор оператора
     * @param newData Новые данные
     * @return Результат операции
     */
    virtual EditResult editOperatorData(int operatorId, const Person& newData) = 0;

    /**
     * @brief Редактировать данные о заказчике
     * @param customerId Идентификатор заказчика
     * @param newData Новые данные
     * @return Результат операции
     */
    virtual EditResult editCustomerData(int customerId, const Person& newData) = 0;

    /**
     * @brief Редактировать описание склада
     * @param warehouseId Идентификатор склада
     * @param newDescription Новое описание склада
     * @return Результат операции
     */
    virtual EditResult editWarehouseDescription(int warehouseId, const QString& newDescription) = 0;

    /**
     * @brief Установить новый статус заказа
     * @param id Идентификатор заказа
     * @param status Новый статус заказа
     * @return Результат операции
     */
    virtual EditResult setOrderStatus(const QString& id, Order::Status status) = 0;

    /**
     * @brief Добавить продукт к заказу
     * @param id Идентификатор заказа
     * @param product Пара артикул-количество
     * @return Результат операции
     */
    virtual EditResult addProductToOrder(const QString& id, const ProductCount& product) = 0;

    /// Удалить пару артикул-описание
    virtual RemoveResult removeDescription(const VendorCode& code) = 0;
    /// Удалить оператора
    virtual RemoveResult removeOperator(int id) = 0;
    /// Удалить заказчика
    virtual RemoveResult removeCustomer(int id) = 0;
    /// Удалить заказ
    virtual RemoveResult removeOrder(const QString& id) = 0;
    /// Удалить склад
    virtual RemoveResult removeWarehouse(int id) = 0;
};
