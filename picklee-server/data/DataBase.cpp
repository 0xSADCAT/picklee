#include "DataBase.hpp"

#include "Filter.hpp"

#include <algorithm>


namespace
{
const static auto addSomeToContainer = [](const auto& some, auto& container, auto predicate) noexcept {
  if (std::find_if(container.begin(), container.end(), predicate) != container.end())
  {
    return AddResult::IdAlreadyExists;
  }
  else
  {
    container.push_back(some);
    return AddResult::Success;
  }
};


const static auto makeIntPredicate = [](const auto& target) noexcept {
  return [&target](const decltype(target)& some) noexcept {
    return some.id() == target.id();
  };
};


const static auto iterById = [](auto& container, const auto& id) noexcept {
  return std::find_if(
      container.begin(), container.end(), [&id](const auto& element) noexcept { return element.id() == id; });
};
}


AddResult DataBase::addDescription(const ProductDescription& description) noexcept
{
  const auto predicate = [&description](const ProductDescription& desc) noexcept {
    return description.code() == desc.code();
  };

  return addSomeToContainer(description, _descriptions, predicate);
}


AddResult DataBase::addOperator(const Operator& oper) noexcept
{
  return addSomeToContainer(oper, _operators, makeIntPredicate(oper));
}


AddResult DataBase::addCustomer(const Customer& customer) noexcept
{
  return addSomeToContainer(customer, _customers, makeIntPredicate(customer));
}


AddResult DataBase::addOrder(const Order& order) noexcept
{
  return addSomeToContainer(order, _orders, makeIntPredicate(order));
}


AddResult DataBase::addWarehouse(const Warehouse& warehouse) noexcept
{
  return addSomeToContainer(warehouse, _warehouses, makeIntPredicate(warehouse));
}


CreateResult DataBase::createOperator(const Person& person) noexcept
{
  int id = _idGenerator.generateOperator();
  _operators.emplace_back(Operator(id, person));
  return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createCustomer(const Person& person) noexcept
{
  int id = _idGenerator.generateClient();
  _customers.emplace_back(id, person);
  return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createOrder(const Operator& oper,
                                   const Customer& customer,
                                   const std::vector<ProductCount>& products) noexcept
{
  std::wstring id = _idGenerator.generateOrder(oper, customer);
  _orders.emplace_back(id, oper.id(), customer.id(), products, Order::Status::InProcessing);
  return CreateResult(CreateResult::Status::Success, id);
}


CreateResult DataBase::createWarehouse(const std::wstring& description, int priority) noexcept
{
  int id = _idGenerator.generateWarehouse();
  _warehouses.emplace_back(id, priority, description);
  return CreateResult(CreateResult::Status::Success, id);
}


void DataBase::findOrder(const Filter& filter, VectorInserter<Order> inserter) const noexcept
{
  for (auto&& order : _orders)
  {
    if (filter.filter(order))
    {
      inserter = order;
    }
  }
}


void DataBase::findCustomer(const Filter& filter, VectorInserter<Customer> inserter) const noexcept
{
  for (auto&& customer : _customers)
  {
    if (filter.filter(customer))
    {
      inserter = customer;
    }
  }
}


void DataBase::findOperator(const Filter& filter, VectorInserter<Operator> inserter) const noexcept
{
  for (auto&& oper : _operators)
  {
    if (filter.filter(oper))
    {
      inserter = oper;
    }
  }
}


void DataBase::findDescription(const Filter& filter, VectorInserter<ProductDescription> inserter) const noexcept
{
  for (auto&& desc : _descriptions)
  {
    if (filter.filter(desc))
    {
      inserter = desc;
    }
  }
}


std::optional<Order> DataBase::orderById(const std::wstring& id) const noexcept
{
  auto it
      = std::find_if(_orders.begin(), _orders.end(), [&id](const Order& order) noexcept { return order.id() == id; });
  if (it != _orders.end())
  {
    return *it;
  }
  else
  {
    return std::nullopt;
  }
}


std::optional<Customer> DataBase::customerById(int id) const noexcept
{
  auto it = std::find_if(
      _customers.begin(), _customers.end(), [id](const Customer& customer) noexcept { return customer.id() == id; });
  if (it != _customers.end())
  {
    return *it;
  }
  else
  {
    return std::nullopt;
  }
}


std::optional<Operator> DataBase::operatorById(int id) const noexcept
{
  auto it = std::find_if(
      _operators.begin(), _operators.end(), [id](const Operator& oper) noexcept { return oper.id() == id; });
  if (it != _operators.end())
  {
    return *it;
  }
  else
  {
    return std::nullopt;
  }
}


std::optional<const Warehouse*> DataBase::warehouseById(int id) const noexcept
{
  auto it = std::find_if(
      _warehouses.begin(), _warehouses.end(), [id](const Warehouse& ware) noexcept { return ware.id() == id; });
  if (it != _warehouses.end())
  {
    return &(*it);
  }
  else
  {
    return std::nullopt;
  }
}


std::optional<ProductDescription> DataBase::productByCode(const VendorCode& code) const noexcept
{
  auto it = std::find_if(_descriptions.begin(), _descriptions.end(), [&code](const ProductDescription& desc) noexcept {
    return desc.code() == code;
  });
  if (it != _descriptions.end())
  {
    return *it;
  }
  else
  {
    return std::nullopt;
  }
}


void DataBase::allProductCountByCode(const VendorCode& code, CountInserter inserter) const noexcept
{
  for (auto&& warehouse : _warehouses)
  {
    auto it = std::find_if(warehouse.products().begin(),
                           warehouse.products().end(),
                           [&code](const ProductCount& prod) noexcept { return prod.code() == code; });
    if (it != warehouse.products().end())
    {
      inserter = {*it, warehouse.id()};
    }
  }
}


const std::vector<Warehouse*> DataBase::warehouses() const noexcept
{
  std::vector<Warehouse*> result;

  for (auto&& item : _warehouses)
  {
    result.push_back(const_cast<Warehouse*>(&item));
  }

  return result;
}


std::tuple<int, int, int> DataBase::ids() const noexcept
{
  return _idGenerator.getAll();
}


void DataBase::resetId(int oper, int cust, int warehouse) noexcept
{
  _idGenerator.reset(oper, cust, warehouse);
}


std::vector<std::pair<int, int>> DataBase::canFetch(const VendorCode& code, int count, bool onlyFull) const noexcept
{
  std::vector<std::pair<int, int>> result;

  for (auto&& ware : _warehouses)
  {
    auto it = std::find_if(
        ware.products().begin(), ware.products().end(), [&code, count, onlyFull](const ProductCount& prod) noexcept {
          if (prod.code() == code)
          {
            if (onlyFull)
            {
              return prod.count() >= count;
            }
            else
            {
              return true;
            }
          }
          else
          {
            return false;
          }
        });

    if (it != ware.products().end())
    {
      result.emplace_back(ware.id(), it->count() >= count ? count : count - it->count());
    }
  }

  return result;
}


ProductResult DataBase::fetch(int warehouseId, const VendorCode& code, int count) noexcept
{
  if (count <= 0)
  {
    return ProductResult::InvalidCount;
  }

  auto ware = std::find_if(_warehouses.begin(), _warehouses.end(), [warehouseId](const Warehouse& ware) noexcept {
    return ware.id() == warehouseId;
  });

  if (ware == _warehouses.end())
  {
    return ProductResult::WarehouseIdNotFound;
  }

  ProductCount prod(code, count);

  if (not ware->canFetch(prod))
  {
    return ProductResult::NotEnoughProduct;
  }
  else
  {
    ware->fetch(prod);
    return ProductResult::Success;
  }
}


ProductResult DataBase::deliver(int warehouseId, const VendorCode& code, int count) noexcept
{
  if (count <= 0)
  {
    return ProductResult::InvalidCount;
  }

  auto ware = std::find_if(_warehouses.begin(), _warehouses.end(), [warehouseId](const Warehouse& ware) noexcept {
    return ware.id() == warehouseId;
  });

  if (ware == _warehouses.end())
  {
    return ProductResult::WarehouseIdNotFound;
  }

  ware->deliver(ProductCount(code, count));

  return ProductResult::Success;
}


EditResult DataBase::editProductDescription(const VendorCode& code, const std::wstring& newDescription) noexcept
{
  auto iter = std::find_if(_descriptions.begin(),
                           _descriptions.end(),
                           [&code](const ProductDescription& prod) noexcept { return prod.code() == code; });

  if (iter == _descriptions.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setDescription(newDescription);
    return EditResult::Success;
  }
}


EditResult DataBase::editOperatorData(int operatorId, const Person& newData) noexcept
{
  if (auto iter = iterById(_operators, operatorId); iter == _operators.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setName(newData);
    return EditResult::Success;
  }
}


EditResult DataBase::editCustomerData(int customerId, const Person& newData) noexcept
{
  if (auto iter = iterById(_customers, customerId); iter == _customers.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setName(newData);
    return EditResult::Success;
  }
}


EditResult DataBase::editWarehousePriority(int warehouseId, int newPriority) noexcept
{
  if (auto iter = iterById(_warehouses, warehouseId); iter == _warehouses.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setPriority(newPriority);
    return EditResult::Success;
  }
}


EditResult DataBase::editWarehouseDescription(int warehouseId, const std::wstring& newDescription) noexcept
{
  if (auto iter = iterById(_warehouses, warehouseId); iter == _warehouses.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setDescription(newDescription);
    return EditResult::Success;
  }
}


EditResult DataBase::setOrderStatus(const std::wstring& id, Order::Status status) noexcept
{
  auto iter
      = std::find_if(_orders.begin(), _orders.end(), [&id](const Order& order) noexcept { return order.id() == id; });

  if (iter == _orders.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->setStatus(status);
    return EditResult::Success;
  }
}


EditResult DataBase::addProductToOrder(const std::wstring& id, const ProductCount& product) noexcept
{
  if (product.count() <= 0)
  {
    return EditResult::InvalidData;
  }

  if (auto iter
      = std::find_if(_orders.begin(), _orders.end(), [&id](const Order& order) noexcept { return order.id() == id; });
      iter == _orders.end())
  {
    return EditResult::IdNotFound;
  }
  else
  {
    iter->addProduct(product);
    return EditResult::Success;
  }
}


RemoveResult DataBase::removeDescription(const VendorCode& code) noexcept
{
  auto iter = std::find_if(_descriptions.begin(),
                           _descriptions.end(),
                           [&code](const ProductDescription& prod) noexcept { return prod.code() == code; });

  if (iter == _descriptions.end())
  {
    return RemoveResult::IdNotFound;
  }
  else
  {
    _descriptions.erase(iter);
    return RemoveResult::Success;
  }
}


RemoveResult DataBase::removeOperator(int id) noexcept
{
  if (auto iter = iterById(_operators, id); iter == _operators.end())
  {
    return RemoveResult::IdNotFound;
  }
  else
  {
    _operators.erase(iter);
    return RemoveResult::Success;
  }
}


RemoveResult DataBase::removeCustomer(int id) noexcept
{
  if (auto iter = iterById(_customers, id); iter == _customers.end())
  {
    return RemoveResult::IdNotFound;
  }
  else
  {
    _customers.erase(iter);
    return RemoveResult::Success;
  }
}


RemoveResult DataBase::removeOrder(const std::wstring& id) noexcept
{
  if (auto iter = iterById(_orders, id); iter == _orders.end())
  {
    return RemoveResult::IdNotFound;
  }
  else
  {
    _orders.erase(iter);
    return RemoveResult::Success;
  }
}


RemoveResult DataBase::removeWarehouse(int id) noexcept
{
  if (auto iter = iterById(_warehouses, id); iter == _warehouses.end())
  {
    return RemoveResult::IdNotFound;
  }
  else
  {
    RemoveResult res = iter->products().empty() ? RemoveResult::Success : RemoveResult::WarehouseNotEmpty;
    _warehouses.erase(iter);
    return res;
  }
}


void DataBase::drop() noexcept
{
  _idGenerator.reset(0, 0, 0);
  _orders.clear();
  _operators.clear();
  _customers.clear();
  _warehouses.clear();
  _descriptions.clear();
}
