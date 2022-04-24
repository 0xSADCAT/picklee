#include "DescriptionList.hpp"

#include "Description.hpp"

#include <QScrollArea>
#include <QVBoxLayout>


DescriptionList::DescriptionList(QWidget* parent) : QWidget {parent}
{
  _list = new QVBoxLayout;

  QWidget* widget = new QWidget;
  widget->setLayout(_list);

  _list->setSpacing(0);
  _list->setContentsMargins(0, 0, 0, 0);

  QScrollArea* scroll = new QScrollArea;
  scroll->setWidget(widget);
  scroll->setWidgetResizable(true);

  QVBoxLayout* lay = new QVBoxLayout;
  lay->addWidget(scroll, 0);
  lay->addWidget(new QWidget, 1);
  setLayout(lay);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


void DescriptionList::removeByCode(const QString& code)
{
  for (auto&& obj : _list->children())
  {
    if (auto desc = qobject_cast<Description*>(obj))
    {
      if (desc->code() == code)
      {
        _list->removeWidget(desc);
        return;
      }
    }
  }
}


void DescriptionList::clear()
{
  while (auto item = _list->takeAt(0))
  {
    _list->removeItem(item);
  }
}


void DescriptionList::add(const QString& code, const QString& desc)
{
  auto item = new Description;
  item->loadData(code, desc);
  _list->addWidget(item);

  connect(item, &Description::codeChanged, this, &DescriptionList::codeChanged);
  connect(item, &Description::descChanged, this, &DescriptionList::descriptionChanged);
}


void DescriptionList::editCode(const QString& oldCode, const QString& newCode)
{
  for (auto&& obj : _list->children())
  {
    if (auto desc = qobject_cast<Description*>(obj))
    {
      if (desc->code() == oldCode)
      {
        desc->loadData(newCode, desc->desc());
      }
    }
  }
}


void DescriptionList::editDesc(const QString& code, const QString& newDesc)
{
  for (auto&& obj : _list->children())
  {
    if (auto desc = qobject_cast<Description*>(obj))
    {
      if (desc->code() == code)
      {
        desc->loadData(code, newDesc);
      }
    }
  }
}
