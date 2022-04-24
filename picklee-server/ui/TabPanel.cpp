#include "TabPanel.hpp"


TabPanel::TabPanel(QWidget* parent) : QWidget {parent}
{
  QVBoxLayout* lay = new QVBoxLayout;
  _top = new QVBoxLayout;
  _bottom = new QVBoxLayout;
  QVBoxLayout* sep = new QVBoxLayout;

  // Затычка
  sep->addWidget(new QWidget, 1);

  lay->addLayout(_top, 0);
  lay->addLayout(sep, 1);
  lay->addLayout(_bottom, 0);
  setLayout(lay);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  _top->setSpacing(0);
  _top->setContentsMargins(0, 0, 0, 0);

  _bottom->setSpacing(0);
  _bottom->setContentsMargins(0, 0, 0, 0);

  sep->setSpacing(0);
  sep->setContentsMargins(0, 0, 0, 0);
}


void TabPanel::addTopWidget(QWidget* widget)
{
  if (widget)
  {
    _top->addWidget(widget);
  }
}


void TabPanel::addBottomWidget(QWidget* widget)
{
  if (widget)
  {
    _bottom->addWidget(widget);
  }
}
