#include "Kernel.hpp"
#include "Logger.hpp"
#include "MainWindow.hpp"
#include "data/DBIO.hpp"
#include "data/DataBase.hpp"

#include <QApplication>
#include <string>


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("Picklee server");
  app.setOrganizationName("0xSADCAT");

  Logger::msg(L"Picklee-server started");

  DataBase dataBase;
  DBIO fileIO(app.applicationDirPath().toStdWString());

  Logger::msg(L"Database path " + fileIO.dir().string<wchar_t>());

  kernel::init(dataBase, fileIO);

  MainWindow window;
  window.show();

  kernel::setDescriptionPresenter(&window);
  kernel::loadDataBase();

  int code = app.exec();

  kernel::saveDataBase();
  Logger::msg(L"Picklee-server finished with code " + std::to_wstring(code));

  return code;
}
