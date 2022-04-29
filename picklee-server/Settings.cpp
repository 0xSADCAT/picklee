#include "Settings.hpp"

#include <QApplication>


namespace
{
QSettings* instance = nullptr;
}


QSettings* settings::get()
{
  if (instance == nullptr)
  {
    instance = new QSettings(qApp->applicationDirPath() + "/" + qApp->applicationName() + "_settings.ini",
                             QSettings::IniFormat);
  }

  return instance;
}


void settings::del()
{
  if (instance)
  {
    delete instance;
    instance = nullptr;
  }
}
