#include "InfoWidget.hpp"

#include <QLabel>
#include <QVBoxLayout>


InfoWidget::InfoWidget(QWidget *parent)
    : QWidget{parent}
{
  auto l = new QVBoxLayout;
  l->addWidget(new QLabel("About application"));
  l->addWidget(new QLabel("In DEV"));
  setLayout(l);
}
