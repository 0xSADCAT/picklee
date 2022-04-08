#include "DataBase.hpp"

#include <algorithm>


namespace {
const static auto addSomeToContainer = [](const auto& some, auto& container, auto predicate) {
    if (std::find_if(container.begin(), container.end(), predicate) != container.end()) {
        return AddResult::IdAlreadyExists;
    } else {
        container.push_back(some);
        return AddResult::Success;
    }
};

const static auto makeIntPredicate = [](const auto& target) {
    return [&target](const decltype(target)& some) {
        return some.id() == target.id();
    };
};
}


AddResult DataBase::addDescription(const VendorCode& code, const ProductDescription& description)
{
    const auto predicate = [&code](const ProductDescription& desc) {
        return code == desc.code();
    };

    return addSomeToContainer(description, _descriptions, predicate);
}


AddResult DataBase::addOperator(const Operator& oper)
{
    return addSomeToContainer(oper, _operators, makeIntPredicate(oper));
}


AddResult DataBase::addCustomer(const Customer& customer)
{
    return addSomeToContainer(customer, _customers, makeIntPredicate(customer));
}


AddResult DataBase::addOrder(const Order& order)
{
    return addSomeToContainer(order, _orders, makeIntPredicate(order));
}


CreateResult DataBase::createOperator(const Person& person)
{
    int id = _idGenerator.generateOperator();
    _operators.emplace_back(Operator(id, person));
    return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createCustomer(const Person& person)
{
    int id = _idGenerator.generateClient();
    _customers.emplace_back(id, person);
    return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createOrder(const Operator& oper, const Customer& customer, const std::vector<ProductCount>& products)
{
    QString id = _idGenerator.generateOrder(oper, customer);
    _orders.emplace_back(id, oper.id(), customer.id(), products, Order::Status::InProcessing);
    return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createWarehouse(const QString& description, int priority)
{
    int id = _idGenerator.generateWarehouse();
    _warehouses.emplace_back(id, priority, description);
    return CreateResult(CreateResult::Status::Success, id);
}


std::vector<Order> DataBase::findOrder(const Filter& filter) const
{
}


std::vector<Customer> DataBase::findCustomer(const Filter& filter) const
{
}


std::vector<Operator> DataBase::findOperator(const Filter& filter) const
{
}


std::vector<ProductDescription> DataBase::findDescription(const Filter& filter) const
{
}


std::optional<Order> DataBase::orderById(const QString& id) const
{
}


std::optional<Customer> DataBase::customerById(int id) const
{
}


std::optional<Operator> DataBase::operatorById(int id) const
{
}


std::optional<const Warehouse*> DataBase::warehouseById(int id) const
{
}


std::optional<ProductDescription> DataBase::productByCode(const VendorCode& code) const
{
}


void DataBase::allProductCountByCode(const VendorCode& code, CountInserter inserter) const
{
}


std::vector<std::pair<int, int> > DataBase::canFetch(const VendorCode& code, int count, bool onlyFull) const
{
}


ProductResult DataBase::fetch(int warehouseId, const VendorCode& code, int count)
{
}


ProductResult DataBase::deliver(int warehouseId, const VendorCode& code, int count)
{
}


EditResult DataBase::editProductDescription(const VendorCode& code, const ProductDescription& newDescription)
{
}


EditResult DataBase::editOperatorData(int operatorId, const Person& newData)
{
}


EditResult DataBase::editCustomerData(int customerId, const Person& newData)
{
}


EditResult DataBase::editWarehouseDescription(int warehouseId, const QString& newDescription)
{
}


EditResult DataBase::setOrderStatus(const QString& id, Order::Status status)
{
}


EditResult DataBase::addProductToOrder(const QString& id, const ProductCount& product)
{
}


RemoveResult DataBase::removeDescription(const VendorCode& code)
{
}


RemoveResult DataBase::removeOperator(int id)
{
}


RemoveResult DataBase::removeCustomer(int id)
{
}


RemoveResult DataBase::removeOrder(const QString& id)
{
}


RemoveResult DataBase::removeWarehouse(int id)
{
}
