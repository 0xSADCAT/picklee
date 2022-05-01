#include "MainWindow.hpp"

#include "Settings.hpp"
#include "ui/CustomerWidget.hpp"
#include "ui/EditableList.hpp"


MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
  QVariant winSize = settings::get()->value(settings::windowSize);
  QVariant winPos = settings::get()->value(settings::windowPos);
  if (not winSize.isNull() and winSize.isValid() and not winPos.isNull() and winPos.isValid())
  {
    setGeometry(QRect {qvariant_cast<QPoint>(winPos), qvariant_cast<QSize>(winSize)});
  }

  setLayout(new QVBoxLayout);
  auto list = new EditableList;
  list->insert(new CustomerWidget("1", "0xSAD", "0xCAT", "Patron", QDate(2022, 5, 12)));
  list->insert(new CustomerWidget("2", "Some", "Person", "Data", QDate(1970, 1, 1)));
  list->insert(new CustomerWidget("3", "This", "is the", "test", QDate(2022, 2, 1)));
  layout()->addWidget(list);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


MainWindow::~MainWindow()
{
  settings::get()->setValue(settings::windowPos, pos());
  settings::get()->setValue(settings::windowSize, size());

  settings::del();
}
