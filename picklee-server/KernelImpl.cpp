#include "KernelImpl.hpp"

#include "Logger.hpp"
#include "data/Filter.hpp"
#include "data/I_DataBase.hpp"
#include "data/I_FileIO.hpp"


namespace
{

const static Filter k_emptyFilter;


void handle(const std::vector<I_FileIO::Error> errors)
{
  for (auto&& err : errors)
  {
    Logger::err(err.message, err.where);
  }
}


void handle(AddResult addResult, const std::wstring& item)
{
  switch (addResult)
  {
  case AddResult::IdAlreadyExists:
    Logger::err(L"Failed to load data: " + item, L"Id is already exists");
    break;

  case AddResult::InvalidData:
    Logger::err(L"Failed to load data: " + item, L"Invalid data");
    break;

  case AddResult::Success:
    break;

  default:
    PICKLEE_ASSERT(false);
  }
}
}


namespace kernel::impl
{

void loadCustomers(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadCustomers();

  handle(res.errors);

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addCustomer(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadOperators(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadOperators();

  handle(res.errors);

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addOperator(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadDescriptions(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadDescriptions();

  handle(res.errors);

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addDescription(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadOrders(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadOrders();

  handle(res.errors);

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addOrder(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadWarehouses(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadWarehouses();

  handle(res.errors);

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addWarehouse(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadIDs(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto [_1, _2, _3] = fileIO.loadId();
  dataBase.resetId(_1, _2, _3);
}


void saveCustomers(I_DataBase& dataBase, I_FileIO& fileIO)
{
  std::vector<Customer> data;
  dataBase.findCustomer(k_emptyFilter, std::back_inserter(data));
  fileIO.saveCustomers(data);
}


void saveOperators(I_DataBase& dataBase, I_FileIO& fileIO)
{
  std::vector<Operator> data;
  dataBase.findOperator(k_emptyFilter, std::back_inserter(data));
  fileIO.saveOperators(data);
}


void saveDescriptions(I_DataBase& dataBase, I_FileIO& fileIO)
{
  std::vector<ProductDescription> data;
  dataBase.findDescription(k_emptyFilter, std::back_inserter(data));
  fileIO.saveDescriptions(data);
}


void saveOrders(I_DataBase& dataBase, I_FileIO& fileIO)
{
  std::vector<Order> data;
  dataBase.findOrder(k_emptyFilter, std::back_inserter(data));
  fileIO.saveOrders(data);
}


void saveWarehouses(I_DataBase& dataBase, I_FileIO& fileIO)
{
  fileIO.saveWarehouses(dataBase.warehouses());
}


void saveIDs(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto&& [oper, cust, ware] = dataBase.ids();
  fileIO.saveId(oper, cust, ware);
}

}
