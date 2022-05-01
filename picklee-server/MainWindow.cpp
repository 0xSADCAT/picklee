#include "MainWindow.hpp"

#include "Settings.hpp"
#include "ui/EditableList.hpp"
#include "ui/ProductCountWidget.hpp"


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
  list->insert(new ProductCountWidget("500-200-CODE", "source code", 1));
  list->insert(new ProductCountWidget("230-78.YT", "issues", 20000));
  list->insert(new ProductCountWidget("VendorCode", "test element", 3));
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
