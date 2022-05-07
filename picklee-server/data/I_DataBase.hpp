#pragma once

#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <optional>
#include <string>
#include <variant>
#include <vector>


class Filter;


/**
 * Итератор для вставки в контейнер, структура:
 * Список из пар (количество продукта, идентификатор склада)
 */
using CountInserter = std::back_insert_iterator<std::vector<std::pair<ProductCount, int>>>;


/// Результат операции добавления
enum class AddResult
{
  Success,         ///< Успешно
  IdAlreadyExists, ///< Данные с таким идентификатором уже существуют
  InvalidData      ///< Некорректные данные
};


/// Результат операции создания
struct CreateResult
{
  enum class Status
  {
    Success,    ///< Успешно
    InvalidData ///< Некорректные данные
  };

  const Status status;                                      ///< Статус операции
  const std::variant<std::wstring, int, std::monostate> id; ///< Идентификатор, если создание было успешным

  CreateResult(Status status, int id) noexcept : status(status), id(id)
  {
  }

  CreateResult(Status status, const std::wstring& id) noexcept : status(status), id(id)
  {
  }

  CreateResult(Status status) noexcept : status(status), id()
  {
  }
};


/// Результат операций поставки/отгрузки товара со склада
enum class ProductResult
{
  Success,             ///< Успешно
  WarehouseIdNotFound, ///< Идентификатор склада не найден
  VendorCodeNotFound,  ///< Артикул не найден
  NotEnoughProduct,    ///< Недостаточно товара (только для отгрузки)
  InvalidCount         ///< Неверно задано количество
};


enum class EditResult
{
  Success,    ///< Успешно
  IdNotFound, ///< Идентификатор не найден
  InvalidData ///< Некорректные данные
};


/// Результат операции удаления
enum class RemoveResult
{
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
  virtual AddResult addDescription(const ProductDescription& description) noexcept = 0;

  /// Добавить оператора
  virtual AddResult addOperator(const Operator& oper) noexcept = 0;

  /// Добавить заказчика
  virtual AddResult addCustomer(const Customer& customer) noexcept = 0;

  /// Добавить заказ
  virtual AddResult addOrder(const Order& order) noexcept = 0;

  /// Добавить склад
  virtual AddResult addWarehouse(const Warehouse& warehouse) noexcept = 0;

  /// Создать ногово оператора
  virtual CreateResult createOperator(const Person& person) noexcept = 0;

  /// Создать нового заказчика
  virtual CreateResult createCustomer(const Person& person) noexcept = 0;

  /// Создать ногый заказ
  virtual CreateResult
  createOrder(const Operator& oper, const Customer& customer, const std::vector<ProductCount>& products) noexcept = 0;

  /// Создать новый склад
  virtual CreateResult createWarehouse(const std::wstring& description, int priority) noexcept = 0;

  /// Найти заказы по фильтру
  virtual void findOrder(const Filter& filter,
                         std::back_insert_iterator<std::vector<Order>> inserter) const noexcept = 0;

  /// Найти заказчиков по фильтру
  virtual void findCustomer(const Filter& filter,
                            std::back_insert_iterator<std::vector<Customer>> inserter) const noexcept = 0;

  /// Найти операторов по фильтру
  virtual void findOperator(const Filter& filter,
                            std::back_insert_iterator<std::vector<Operator>> inserter) const noexcept = 0;
  /// Найти описания по фильтру
  virtual void findDescription(const Filter& filter,
                               std::back_insert_iterator<std::vector<ProductDescription>> inserter) const noexcept = 0;

  /// Найти конктерный заказ по идентификатору
  virtual std::optional<Order> orderById(const std::wstring& id) const noexcept = 0;
  /// Найти конктерного заказчика по идентификатору
  ///
  virtual std::optional<Customer> customerById(int id) const noexcept = 0;

  /// Найти конктерного оператора по идентификатору
  virtual std::optional<Operator> operatorById(int id) const noexcept = 0;

  /// Найти конктерный склад по идентификатору
  virtual std::optional<const Warehouse*> warehouseById(int id) const noexcept = 0;

  /// Найти конктерное описание по артикулу
  virtual std::optional<ProductDescription> productByCode(const VendorCode& code) const noexcept = 0;

  /**
   * @brief Собрать в итератор все продукты по артикулу
   * @param code Артикул для поиска
   * @param inserter Итератор вставки в конец результирующего контейнера
   *
   * @details Операция вставляет в контейнер по переданному итератору вставки в конец все пары артикул-количество
   *          и идентификатор склада, на котором этот продукт был обнаружен.
   *          Например, если есть 2 склада с артикулом #ar: id = 3, количество = 2 и id = 34, количество = 1, в таком
   *          случае функция вернет следующее:
   *          { {{#ar, 2}, 3},
   *            {{#ar, 1}, 34} }
   */
  virtual void allProductCountByCode(const VendorCode& code, CountInserter inserter) const noexcept = 0;

  /// Список указателей на все склады
  virtual const std::vector<Warehouse*> warehouses() const noexcept = 0;

  /// Установить новые значения идентификаторов для генератора
  virtual void resetId(int oper, int cust, int warehouse) noexcept = 0;

  /**
   * @brief Текущие значения генератора идентификаторов
   * @return По порядку: оператор, заказчик, склад
   */
  virtual std::tuple<int, int, int> ids() const noexcept = 0;

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
  virtual std::vector<std::pair<int, int>>
  canFetch(const VendorCode& code, int count, bool onlyFull) const noexcept = 0;

  /**
   * @brief Получить товар со склада
   * @param warehouseId Идентификатор склада
   * @param code Артикул товара
   * @param count Количество для получения
   * @return Результат операции
   */
  virtual ProductResult fetch(int warehouseId, const VendorCode& code, int count) noexcept = 0;

  /**
   * @brief Поставить товар на склад
   * @param warehouseId Идентификатор склада
   * @param code Артикул товара
   * @param count Количество для поставки
   * @return Результат операции
   */
  virtual ProductResult deliver(int warehouseId, const VendorCode& code, int count) noexcept = 0;

  /**
   * @brief Редактировать описание продукта
   * @param code Артикул товара
   * @param newDescription Новое описание товара
   * @return Результат операции
   */
  virtual EditResult editProductDescription(const VendorCode& code, const std::wstring& newDescription) noexcept = 0;

  /**
   * @brief Редактировать данные об операторе
   * @param operatorId Идентификатор оператора
   * @param newData Новые данные
   * @return Результат операции
   */
  virtual EditResult editOperatorData(int operatorId, const Person& newData) noexcept = 0;

  /**
   * @brief Редактировать данные о заказчике
   * @param customerId Идентификатор заказчика
   * @param newData Новые данные
   * @return Результат операции
   */
  virtual EditResult editCustomerData(int customerId, const Person& newData) noexcept = 0;

  /**
   * @brief Редактировать приоритет склада
   * @param warehouseId Идентификатор склада
   * @param newPriority Новый приоритет
   * @return Результат операции
   */
  virtual EditResult editWarehousePriority(int warehouseId, int newPriority) noexcept = 0;

  /**
   * @brief Редактировать описание склада
   * @param warehouseId Идентификатор склада
   * @param newDescription Новое описание склада
   * @return Результат операции
   */
  virtual EditResult editWarehouseDescription(int warehouseId, const std::wstring& newDescription) noexcept = 0;

  /**
   * @brief Установить новый статус заказа
   * @param id Идентификатор заказа
   * @param status Новый статус заказа
   * @return Результат операции
   */
  virtual EditResult setOrderStatus(const std::wstring& id, Order::Status status) noexcept = 0;

  /**
   * @brief Добавить продукт к заказу
   * @param id Идентификатор заказа
   * @param product Пара артикул-количество
   * @return Результат операции
   */
  virtual EditResult addProductToOrder(const std::wstring& id, const ProductCount& product) noexcept = 0;

  /// Удалить пару артикул-описание
  virtual RemoveResult removeDescription(const VendorCode& code) noexcept = 0;

  /// Удалить оператора
  virtual RemoveResult removeOperator(int id) noexcept = 0;

  /// Удалить заказчика
  virtual RemoveResult removeCustomer(int id) noexcept = 0;

  /// Удалить заказ
  virtual RemoveResult removeOrder(const std::wstring& id) noexcept = 0;

  /// Удалить склад
  virtual RemoveResult removeWarehouse(int id) noexcept = 0;

  /// Очистить базу данных
  virtual void drop() noexcept = 0;
};
