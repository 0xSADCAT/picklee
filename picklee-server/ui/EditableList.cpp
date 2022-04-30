#include "EditableList.hpp"

#include "EditableWidget.hpp"

#include <QScrollArea>
#include <QVBoxLayout>


EditableList::EditableList(QWidget* parent) : QWidget {parent}
{
  auto scrollArea = new QScrollArea;
  auto scrollLayout = new QVBoxLayout;
  _layout = new QVBoxLayout;
  auto mainLayout = new QVBoxLayout;
  auto scrollWidget = new QWidget;

  _layout->setSpacing(0);
  _layout->setContentsMargins(0, 0, 0, 0);

  scrollLayout->addLayout(_layout, 0);
  scrollLayout->addStretch(1);
  scrollLayout->setSpacing(0);
  scrollLayout->setContentsMargins(0, 0, 0, 0);

  scrollWidget->setLayout(scrollLayout);

  scrollArea->setWidget(scrollWidget);
  scrollArea->setWidgetResizable(true);

  mainLayout->addWidget(scrollArea);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


void EditableList::insert(EditableWidget* widget)
{
  assert(not _widgets.contains(widget));
  assert(widget != nullptr);

  _widgets << widget;
  _layout->addWidget(widget);
  connect(widget, &EditableWidget::selected, this, &EditableList::onWidgetSelected);
}


void EditableList::remove(EditableWidget* widget)
{
  assert(widget != nullptr);
  assert(_widgets.contains(widget));

  _widgets.removeOne(widget);
  _layout->removeWidget(widget);
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

  assert(widget != nullptr);
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
