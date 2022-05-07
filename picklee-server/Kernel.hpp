#pragma once


class I_DataBase;
class I_GuiWidget;
class I_FileIO;
class I_ProductDescriptionPresenter;


namespace kernel
{
void init(I_DataBase& dataBase, I_FileIO& fileIO);

void loadDataBase();
void saveDataBase();

void setDescriptionPresenter(I_ProductDescriptionPresenter* presenter);
}
