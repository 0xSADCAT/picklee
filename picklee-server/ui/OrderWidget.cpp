#include "OrderWidget.hpp"

#include "EditableList.hpp"
#include "ProductCountWidget.hpp"
#include "SpoilerWidget.hpp"

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>


namespace
{
constexpr std::wstring_view inProcessing = L"В обработке";
constexpr std::wstring_view waitingForDelivery = L"Ожидает поставки";
constexpr std::wstring_view readyToIssue = L"Готов к выдаче";
constexpr std::wstring_view issued = L"Выдано";
}


OrderWidget::OrderWidget(const QString& newId,
                         const QString& operId,
                         const QString& custId,
                         const QList<ProductCountWidget*>& products,
                         Order::Status status)
    : EditableWidget {nullptr}
{
}


void OrderWidget::setProducts(QList<ProductCountWidget*> products)
{
}


EditableList* OrderWidget::products() const
{
  return (EditableList*) qobject_cast<EditableWidget*>(_productWidget->content());
}


void OrderWidget::setStatus(Order::Status status)
{
}


Order::Status OrderWidget::status() const
{
  return statusFromString(_statusLabel->text());
}


void OrderWidget::setData(const QString& id, const QString& operId, const QString& custId)
{
}


std::tuple<QString, QString, QString> OrderWidget::data() const
{
  return {_idLabel->text(), _operIdLabel->text(), _custIdLabel->text()};
}


void OrderWidget::onEditMode()
{
}


void OrderWidget::onViewMode(bool reset)
{
}


Order::Status OrderWidget::statusFromString(const QString& string)
{
  static constexpr auto str = [](std::wstring_view view) {
    return QString::fromStdWString(std::wstring(view));
  };

  if (string == str(inProcessing))
  {
    return Order::Status::InProcessing;
  }
  else if (string == str(issued))
  {
    return Order::Status::Issued;
  }
  else if (string == str(waitingForDelivery))
  {
    return Order::Status::WaitingForDelivery;
  }
  else if (string == str(readyToIssue))
  {
    return Order::Status::ReadyToIssue;
  }
  else
  {
    throw std::runtime_error("Invalid imput");
  }
}


QList<QPair<QString, int>> OrderWidget::makeList() const
{
  QList<QPair<QString, int>> result;

  if (EditableList* list = qobject_cast<EditableList*>(_productWidget->content()))
  {
    for (auto&& widget : *list)
    {
      if (ProductCountWidget* prod = qobject_cast<ProductCountWidget*>(widget))
      {
        auto&& [code, unused] = prod->data();
        result << QPair(code, prod->count());
      }
      else
      {
        // widget почему-то не ProductCountWidget
        assert(false);
      }
    }
  }
  else
  {
    // В контенте почему-то не EditableList
    assert(false);
  }

  return result;
}
