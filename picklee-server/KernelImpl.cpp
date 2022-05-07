#include "KernelImpl.hpp"

#include "Logger.hpp"
#include "data/Filter.hpp"
#include "data/I_DataBase.hpp"
#include "data/I_FileIO.hpp"
#include "ui/I_ProductDescriptionPresenter.hpp"


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

  Logger::msg(L"Found " + std::to_wstring(res.results.size()) + L" customers");

  std::sort(
      res.results.begin(), res.results.end(), [](const Customer& c1, const Customer& c2) { return c1.id() < c2.id(); });

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

  Logger::msg(L"Found " + std::to_wstring(res.results.size()) + L" operators");

  std::sort(
      res.results.begin(), res.results.end(), [](const Operator& c1, const Operator& c2) { return c1.id() < c2.id(); });

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addOperator(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
  }
}


void loadDescriptions(I_DataBase& dataBase, I_FileIO& fileIO, I_ProductDescriptionPresenter& presenter)
{
  auto res = fileIO.loadDescriptions();

  handle(res.errors);

  Logger::msg(L"Found " + std::to_wstring(res.results.size()) + L" descriptions");

  std::sort(res.results.begin(), res.results.end(), [](const ProductDescription& c1, const ProductDescription& c2) {
    return c1.code().str() < c2.code().str();
  });

  for (auto&& item : res.results)
  {
    if (auto addRes = dataBase.addDescription(item); addRes != AddResult::Success)
    {
      handle(addRes, item.toString());
    }
    else
    {
      presenter.addDesc(item.code().str(), item.description());
    }
  }
}


void loadOrders(I_DataBase& dataBase, I_FileIO& fileIO)
{
  auto res = fileIO.loadOrders();

  handle(res.errors);

  Logger::msg(L"Found " + std::to_wstring(res.results.size()) + L" orders");

  std::sort(res.results.begin(), res.results.end(), [](const Order& c1, const Order& c2) { return c1.id() < c2.id(); });

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

  Logger::msg(L"Found " + std::to_wstring(res.results.size()) + L" warehouses");

  std::sort(res.results.begin(), res.results.end(), [](const Warehouse& c1, const Warehouse& c2) {
    return c1.id() < c2.id();
  });

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


namespace kernel::handler
{

namespace
{

I_ProductDescriptionPresenter* kh_descPres = nullptr;

}


void descriptionChanged(I_DataBase& dataBase,
                        const std::wstring& code,
                        const std::wstring& newCode,
                        const std::wstring& desc)
{
  PICKLEE_ASSERT(kh_descPres != nullptr);

  Logger::msg(L"Description changed for VendorCode " + code + L", new VendorCode: " + newCode + L", description: \""
              + desc + L"\"");

  if (code == newCode)
  {
    auto editRes = dataBase.editProductDescription(code, desc);
    if (editRes != EditResult::Success)
    {
      Logger::err(L"Failed to edit description: ",
                  editRes == EditResult::InvalidData ? L"Invalid description data" : L"Vendor code not found");
    }
  }
  else
  {
    auto removeRes = dataBase.removeDescription(code);

    if (removeRes != RemoveResult::Success)
    {
      Logger::err(L"Failed to edit code", L"Vendor code " + code + L" not found");
      return;
    }

    auto addRes = dataBase.addDescription({newCode, desc});

    if (addRes != AddResult::Success)
    {
      handle(addRes, L"Adding new after remove");
      dataBase.addDescription({code, desc});
      kh_descPres->editDesc(newCode, code, desc);
    }
  }
}


void setDescriptionPresenter(I_ProductDescriptionPresenter* presenter)
{
  PICKLEE_ASSERT(presenter != nullptr);

  kh_descPres = presenter;
}

}
