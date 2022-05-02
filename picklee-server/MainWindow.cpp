#include "MainWindow.hpp"

#include "Settings.hpp"
#include "ui/EditableList.hpp"
#include "ui/OrderWidget.hpp"
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
  list->insert(new OrderWidget("1-3-02.05.2022-16:42",
                               "1",
                               "3",
                               {new ProductCountWidget("500-255-3", "Some thing", 4),
                                new ProductCountWidget("500-255-4", "Some thing 2", 5),
                                new ProductCountWidget("500-255-5", "Some thing 3", 6),
                                new ProductCountWidget("500-255-6", "Some thing 4", 7)},
                               Order::Status::InProcessing));
  list->insert(new OrderWidget(
      "1-3-02.05.2022-16:42",
      "1",
      "3",
      {new ProductCountWidget("0xSAD", "Dev", 1), new ProductCountWidget("0xCAT", "Lazy developer", 20)},
      Order::Status::WaitingForDelivery));
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
