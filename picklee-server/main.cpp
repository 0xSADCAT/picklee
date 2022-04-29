#include "MainWindow.hpp"
#include "Settings.hpp"

#include <QApplication>


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("Picklee server");
  app.setOrganizationName("0xSADCAT");

  MainWindow window;
  window.show();

  int code = app.exec();

  return code;
}
