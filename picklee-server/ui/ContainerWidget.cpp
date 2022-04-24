#include "ContainerWidget.hpp"


ContainerWidget::ContainerWidget(QWidget* parent) : QWidget(parent)
{
  _layout = new QVBoxLayout;
  setLayout(_layout);
  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


void ContainerWidget::setWidgets(QList<QWidget*> widgets)
{
  if (not _widgets.empty())
  {
    for (auto&& wgt : _widgets)
    {
      _layout->removeWidget(wgt);
      wgt->deleteLater();
    }

    _widgets.clear();
    _current = nullptr;
  }

  _widgets = std::move(widgets);
  for (auto&& wgt : _widgets)
  {
    _layout->addWidget(wgt);
    wgt->setVisible(false);
  }

  if (not _widgets.empty())
  {
    _widgets.first()->setVisible(true);
    _current = _widgets.first();
  }
}


QWidget* ContainerWidget::current() const
{
  return _current;
}


void ContainerWidget::showWidget(QWidget* widget)
{
  if (not widget)
  {
    return;
  }

  if (_widgets.contains(widget))
  {
    _current->setVisible(false);
    _current = widget;
    _current->setVisible(true);
  }
}


void ContainerWidget::showWidget(int number)
{
  if (number >= _widgets.count())
  {
    return;
  }

  _current->setVisible(false);
  _current = _widgets[number];
  _current->setVisible(true);
}
