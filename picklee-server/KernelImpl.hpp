#pragma once

#include <string>


class I_DataBase;
class I_FileIO;
class I_ProductDescriptionPresenter;


namespace kernel::impl
{

void loadCustomers(I_DataBase& dataBase, I_FileIO& fileIO);
void loadOperators(I_DataBase& dataBase, I_FileIO& fileIO);
void loadDescriptions(I_DataBase& dataBase, I_FileIO& fileIO, I_ProductDescriptionPresenter& presenter);
void loadOrders(I_DataBase& dataBase, I_FileIO& fileIO);
void loadWarehouses(I_DataBase& dataBase, I_FileIO& fileIO);
void loadIDs(I_DataBase& dataBase, I_FileIO& fileIO);

void saveCustomers(I_DataBase& dataBase, I_FileIO& fileIO);
void saveOperators(I_DataBase& dataBase, I_FileIO& fileIO);
void saveDescriptions(I_DataBase& dataBase, I_FileIO& fileIO);
void saveOrders(I_DataBase& dataBase, I_FileIO& fileIO);
void saveWarehouses(I_DataBase& dataBase, I_FileIO& fileIO);
void saveIDs(I_DataBase& dataBase, I_FileIO& fileIO);

}


namespace kernel::handler
{

void setDescriptionPresenter(I_ProductDescriptionPresenter* presenter);

void descriptionChanged(I_DataBase& dataBase,
                        const std::wstring& code,
                        const std::wstring& newCode,
                        const std::wstring& desc);

}
