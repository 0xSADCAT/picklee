#pragma once


class I_DataBase;
class I_FileIO;


namespace kernel::impl
{

void loadCustomers(I_DataBase& dataBase, I_FileIO& fileIO);
void loadOperators(I_DataBase& dataBase, I_FileIO& fileIO);
void loadDescriptions(I_DataBase& dataBase, I_FileIO& fileIO);
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
