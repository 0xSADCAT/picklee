#include "MainWindow.hpp"

#include "Settings.hpp"
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
  layout()->addWidget(new ProductDescriptionWidget("ProdID", "ProdDescription"));
  if (auto l = qobject_cast<QVBoxLayout*>(layout()))
  {
    l->addStretch(1);
  }
}


MainWindow::~MainWindow()
{
  settings::get()->setValue(settings::windowPos, pos());
  settings::get()->setValue(settings::windowSize, size());

  settings::del();
}
