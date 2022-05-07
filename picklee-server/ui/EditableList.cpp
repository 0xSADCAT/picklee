#include "EditableList.hpp"

#include "../Logger.hpp"
#include "EditableWidget.hpp"

#include <QScrollArea>
#include <QVBoxLayout>


EditableList::EditableList(bool hasScroll) : QWidget {nullptr}
{
  _layout = new QVBoxLayout;

  _layout->setSpacing(0);
  _layout->setContentsMargins(0, 0, 0, 0);

  if (hasScroll)
  {
    auto scrollArea = new QScrollArea;
    auto scrollLayout = new QVBoxLayout;
    auto mainLayout = new QVBoxLayout;
    auto scrollWidget = new QWidget;

    scrollLayout->addLayout(_layout, 0);
    scrollLayout->addStretch(1);
    scrollLayout->setSpacing(0);
    scrollLayout->setContentsMargins(0, 0, 0, 0);

    scrollWidget->setLayout(scrollLayout);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
  }
  else
  {
    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(_layout, 0);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
  }

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


void EditableList::insert(EditableWidget* widget)
{
  PICKLEE_ASSERT(not _widgets.contains(widget));
  PICKLEE_ASSERT(widget != nullptr);

  _widgets << widget;
  _layout->addWidget(widget);
  connect(widget, &EditableWidget::selected, this, &EditableList::onWidgetSelected);
}


void EditableList::remove(EditableWidget* widget)
{
  PICKLEE_ASSERT(widget != nullptr);
  PICKLEE_ASSERT(_widgets.contains(widget));

  _widgets.removeOne(widget);
  _layout->removeWidget(widget);
  widget->deleteLater();
}


void EditableList::clear(bool deleteWidgets)
{
  for (auto&& widget : _widgets)
  {
    _layout->removeWidget(widget);

    if (deleteWidgets)
    {
      widget->deleteLater();
    }
  }

  _widgets.clear();
}


QList<EditableWidget*>::Iterator EditableList::begin()
{
  return _widgets.begin();
}


QList<EditableWidget*>::Iterator EditableList::end()
{
  return _widgets.end();
}


EditableWidget* EditableList::selected() const
{
  return _selected;
}


void EditableList::setSelected(EditableWidget* newSelected)
{
  if (_selected)
  {
    _selected->setViewMode(true);
  }

  _selected = newSelected;

  if (_selected)
  {
    _selected->select();
  }
}


void EditableList::onWidgetSelected()
{
  EditableWidget* widget = qobject_cast<EditableWidget*>(sender());

  PICKLEE_ASSERT(widget != nullptr);

  if (widget == nullptr)
  {
    return;
  }

  if (_selected)
  {
    _selected->setViewMode(true);
  }

  _selected = widget;
}
