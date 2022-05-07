#include "Kernel.hpp"

#include "KernelImpl.hpp"
#include "Logger.hpp"

#include <cassert>


namespace
{
I_DataBase* k_dataBase = nullptr;
I_FileIO* k_fileIO = nullptr;
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

  impl::loadCustomers(*k_dataBase, *k_fileIO);
  impl::loadDescriptions(*k_dataBase, *k_fileIO);
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

}
