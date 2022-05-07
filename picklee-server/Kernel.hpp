#pragma once


class I_DataBase;
class I_GuiWidget;
class I_FileIO;


namespace kernel
{
void init(I_DataBase& dataBase, I_FileIO& fileIO);

void loadDataBase();
void saveDataBase();
}
