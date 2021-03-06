#include "Kernel.hpp"

#include "KernelImpl.hpp"
#include "Logger.hpp"
#include "ui/I_ProductDescriptionPresenter.hpp"

#include <cassert>


namespace
{

I_DataBase* k_dataBase = nullptr;
I_FileIO* k_fileIO = nullptr;

I_ProductDescriptionPresenter* k_descPres = nullptr;
}


namespace kernel
{

void init(I_DataBase& dataBase, I_FileIO& fileIO)
{
  k_dataBase = &dataBase;
  k_fileIO = &fileIO;
}


void loadDataBase()
{
  PICKLEE_ASSERT(k_fileIO != nullptr);
  PICKLEE_ASSERT(k_dataBase != nullptr);
  PICKLEE_ASSERT(k_descPres != nullptr);

  impl::loadCustomers(*k_dataBase, *k_fileIO);
  impl::loadDescriptions(*k_dataBase, *k_fileIO, *k_descPres);
  impl::loadIDs(*k_dataBase, *k_fileIO);
  impl::loadOperators(*k_dataBase, *k_fileIO);
  impl::loadOrders(*k_dataBase, *k_fileIO);
  impl::loadWarehouses(*k_dataBase, *k_fileIO);
}


void saveDataBase()
{
  PICKLEE_ASSERT(k_fileIO != nullptr);
  PICKLEE_ASSERT(k_dataBase != nullptr);

  impl::saveCustomers(*k_dataBase, *k_fileIO);
  impl::saveDescriptions(*k_dataBase, *k_fileIO);
  impl::saveIDs(*k_dataBase, *k_fileIO);
  impl::saveOperators(*k_dataBase, *k_fileIO);
  impl::saveOrders(*k_dataBase, *k_fileIO);
  impl::saveWarehouses(*k_dataBase, *k_fileIO);
}


void setDescriptionPresenter(I_ProductDescriptionPresenter* presenter)
{
  PICKLEE_ASSERT(k_descPres == nullptr);
  PICKLEE_ASSERT(presenter != nullptr);
  PICKLEE_ASSERT(k_dataBase != nullptr);

  I_DataBase& db = *k_dataBase;

  k_descPres = presenter;
  handler::setDescriptionPresenter(presenter);
  presenter->setDescChangeHandler([&db](const std::wstring& _1, const std::wstring& _2, const std::wstring& _3) {
    handler::descriptionChanged(db, _1, _2, _3);
  });
}

}
