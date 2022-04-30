#include "MainWindow.hpp"

#include "Settings.hpp"
#include "ui/EditableList.hpp"
#include "ui/ProductDescriptionWidget.hpp"


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
  list->insert(new ProductDescriptionWidget("12345", "dfgdfg"));
  list->insert(new ProductDescriptionWidget("2323", "dgsfgdfg"));
  list->insert(new ProductDescriptionWidget("4353", "dfgdfgdfgsfdg"));
  list->insert(new ProductDescriptionWidget("234", "sget34t 3t 3t tt"));
  list->insert(new ProductDescriptionWidget("23423", "34 rtrt rter r"));
  list->insert(new ProductDescriptionWidget("21312", "g et fdg dfg d"));
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
