#include "MainWindow.hpp"

#include "Settings.hpp"
#include "ui/EditableList.hpp"
#include "ui/ProductCountWidget.hpp"
#include "ui/WarehouseWidget.hpp"


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
  list->insert(new WarehouseWidget("1",
                                   "Основной склад",
                                   1,
                                   {new ProductCountWidget("A4", "Лист бумаги", 4),
                                    new ProductCountWidget("C-19.22", "Двухлетняя маска", 5),
                                    new ProductCountWidget("124561.97964.4564.2764", "Какая-то хреновина", 1),
                                    new ProductCountWidget("500-255-6", "Изолента", 7)}));
  list->insert(new WarehouseWidget("2",
                                   "Барахолка в чулане",
                                   -4,
                                   {new ProductCountWidget("255-63-ZQ.2", "Ведро гвоздей", 1),
                                    new ProductCountWidget("Au-997-65", "Кубометр золота", 20)}));
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
