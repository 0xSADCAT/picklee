#include "DescriptionMainWidget.hpp"

#include "DescriptionInfoWidget.hpp"
#include "DescriptionWidget.hpp"

#include <QScrollArea>
#include <QVBoxLayout>
#include <cassert>


DescriptionMainWidget::DescriptionMainWidget(QWidget *parent)
    : QWidget{parent}
{
  _widgetsLayout = new QVBoxLayout;
  QScrollArea* scroll = new QScrollArea;
  QVBoxLayout* mainLayout = new QVBoxLayout;
  QWidget* scrollWidget = new QWidget;

  QVBoxLayout* swLayout = new QVBoxLayout;
  swLayout->addLayout(_widgetsLayout, 0);
  swLayout->addWidget(new QWidget, 1);

  scrollWidget->setLayout(swLayout);
  scroll->setWidget(scrollWidget);
  scroll->setWidgetResizable(true);

  mainLayout->addWidget(scroll);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  _widgetsLayout->setSpacing(0);
  _widgetsLayout->setContentsMargins(0, 0, 0, 0);
}


void DescriptionMainWidget::setInfoWidget(DescriptionInfoWidget* widget)
{
  assert(widget != nullptr);
  assert(_infoWidget == nullptr);

  _infoWidget = widget;
  _infoWidget->connectTo(this);
}


void DescriptionMainWidget::addDescription(const QString& id, const QString& description)
{
  for (auto&& [eid, __unused] : _descriptions)
  {
    if (eid == id)
    {
      return;
    }
  }

  DescriptionWidget* widget = new DescriptionWidget(id, description);
  _descriptions.append({id, widget});
  connect(widget, &DescriptionWidget::clicked, this, &DescriptionMainWidget::onElementClicked);
  _widgetsLayout->addWidget(widget);
}


void DescriptionMainWidget::removeDescription(const QString& id)
{
  for (auto&& pair : _descriptions)
  {
    auto&& [eid, widget] = pair;
    if (eid == id)
    {
      _descriptions.removeOne(pair);
      _widgetsLayout->removeWidget(widget);
      widget->deleteLater();
      return;
    }
  }
}


void DescriptionMainWidget::editData(const QString& id, const QString& newId, const QString& newDescription)
{
  assert(not newId.isEmpty());

  for (auto&& [eid, widget] : _descriptions)
  {
    if (eid == id)
    {
      if (auto desc = qobject_cast<DescriptionWidget*>(widget))
      {
        desc->setId(newId);
        desc->setDesc(newDescription);
        return;
      }
    }
  }
}


void DescriptionMainWidget::editDescription(const QString& id, const QString& newDescription)
{
  for (auto&& [eid, widget] : _descriptions)
  {
    if (eid == id)
    {
      if (auto desc = qobject_cast<DescriptionWidget*>(widget))
      {
        desc->setDesc(newDescription);
        return;
      }
    }
  }
}


void DescriptionMainWidget::editId(const QString& id, const QString& newId)
{
  assert(not newId.isEmpty());

  for (auto&& [eid, widget] : _descriptions)
  {
    if (eid == id)
    {
      if (auto desc = qobject_cast<DescriptionWidget*>(widget))
      {
        desc->setId(newId);
        eid = newId;
        return;
      }
    }
  }
}


void DescriptionMainWidget::onEditDone(const QString& oldId, const QString& newId, const QString& newDescription)
{
  assert(not newId.isEmpty());

  for (auto&& [eid, widget] : _descriptions)
  {
    if (eid == oldId)
    {
      if (auto desc = qobject_cast<DescriptionWidget*>(widget))
      {
        if (desc->id() != newId)
        {
          desc->setId(newId);
          emit idChanged(oldId, newId);
        }

        if (desc->desc() != newDescription)
        {
          desc->setDesc(newDescription);
          emit descriptionChanged(desc->id(), newDescription);
        }

        return;
      }
    }
  }
}


void DescriptionMainWidget::onDescriptionDeleted(const QString& id)
{
  emit elementDeleted(id);
  removeDescription(id);
}


void DescriptionMainWidget::onElementClicked()
{
  if (DescriptionWidget* from = qobject_cast<DescriptionWidget*>(sender()))
  {
    for (auto&& [unused, widget] : _descriptions)
    {
      if (auto desc = qobject_cast<DescriptionWidget*>(widget))
      {
        desc->unselect();
      }
    }

    from->setSelected();

    assert(_infoWidget);
    if (_infoWidget)
    {
      _infoWidget->setData(from->id(), from->desc());
    }
  }
}
