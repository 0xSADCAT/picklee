#include "OrderWidget.hpp"

#include "EditableList.hpp"
#include "ProductCountWidget.hpp"
#include "SpoilerWidget.hpp"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>


namespace
{
constexpr std::wstring_view inProcessing = L"В обработке";
constexpr std::wstring_view waitingForDelivery = L"Ожидает поставки";
constexpr std::wstring_view readyToIssue = L"Готов к выдаче";
constexpr std::wstring_view issued = L"Выдано";


constexpr auto str = [](std::wstring_view string) {
  return QString::fromStdWString(std::wstring(string));
};


constexpr auto to_string = [](Order::Status status) {
  switch (status)
  {
  case Order::Status::InProcessing:
    return str(inProcessing);

  case Order::Status::Issued:
    return str(issued);

  case Order::Status::ReadyToIssue:
    return str(readyToIssue);

  case Order::Status::WaitingForDelivery:
    return str(waitingForDelivery);

  default:
    assert(false);
    return QString();
  }
};
}


OrderWidget::OrderWidget(const QString& id,
                         const QString& operId,
                         const QString& custId,
                         const QList<ProductCountWidget*>& products,
                         Order::Status status)
    : EditableWidget {false}
{
  QStringList statusList = {str(inProcessing), str(waitingForDelivery), str(readyToIssue), str(issued)};

  _idLabel = new QLabel(id);
  _idEdit = new QLineEdit;
  _idEdit->setVisible(false);

  _operIdLabel = new QLabel(operId);
  _operIdEdit = new QLineEdit;
  _operIdEdit->setVisible(false);

  _custIdLabel = new QLabel(custId);
  _custIdEdit = new QLineEdit;
  _custIdEdit->setVisible(false);

  QWidget* prodHeader = new QLabel("Продукты");
  EditableList* prodContent = new EditableList(false);
  for (auto&& widget : products)
  {
    assert(widget != nullptr);
    widget->lockEdit();
    connect(widget, &ProductCountWidget::dataChanged, this, &OrderWidget::onInnerDataChanged);
    prodContent->insert(widget);
  }
  _productWidget = new SpoilerWidget(prodHeader, prodContent);
  _productWidget->hideContent();

  _statusLabel = new QLabel(to_string(status));
  _statusEdit = new QComboBox;
  _statusEdit->addItems(statusList);
  _statusEdit->setDuplicatesEnabled(false);
  _statusEdit->setVisible(false);

  QHBoxLayout* topLayout = new QHBoxLayout;
  topLayout->addWidget(_idLabel, 1);
  topLayout->addWidget(_idEdit, 1);
  topLayout->addSpacing(5);
  topLayout->addWidget(_operIdLabel, 1);
  topLayout->addWidget(_operIdEdit, 1);
  topLayout->addSpacing(5);
  topLayout->addWidget(_custIdLabel, 1);
  topLayout->addWidget(_custIdEdit, 1);
  topLayout->addSpacing(5);
  topLayout->addWidget(_statusLabel, 1);
  topLayout->addWidget(_statusEdit, 1);

  topLayout->setSpacing(0);
  topLayout->setContentsMargins(0, 0, 0, 0);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(topLayout, 0);
  mainLayout->addWidget(_productWidget, 1);

  mainLayout->setSpacing(0);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  contentWidget()->setLayout(mainLayout);
}


void OrderWidget::addProduct(ProductCountWidget* product)
{
  assert(product);

  connect(product, &ProductCountWidget::dataChanged, this, &OrderWidget::onInnerDataChanged);

  if (auto list = qobject_cast<EditableList*>(_productWidget->content()))
  {
    list->insert(product);
  }
  else
  {
    assert(false);
  }
}


EditableList* OrderWidget::products() const
{
  return (EditableList*) qobject_cast<EditableWidget*>(_productWidget->content());
}


void OrderWidget::setStatus(Order::Status status)
{
  _statusLabel->setText(QString::fromStdWString(Order::statusToString(status)));
  _statusEdit->setCurrentIndex(static_cast<int>(status));
}


Order::Status OrderWidget::status() const
{
  return statusFromString(_statusLabel->text());
}


void OrderWidget::setData(const QString& id, const QString& operId, const QString& custId)
{
  _idLabel->setText(id);
  _idEdit->setText(id);

  _operIdLabel->setText(operId);
  _operIdEdit->setText(operId);

  _custIdLabel->setText(custId);
  _custIdEdit->setText(custId);
}


std::tuple<QString, QString, QString> OrderWidget::data() const
{
  return {_idLabel->text(), _operIdLabel->text(), _custIdLabel->text()};
}


void OrderWidget::onEditMode()
{
  _idLabel->setVisible(false);
  _operIdLabel->setVisible(false);
  _custIdLabel->setVisible(false);
  _statusLabel->setVisible(false);

  _idEdit->setVisible(true);
  _operIdEdit->setVisible(true);
  _custIdEdit->setVisible(true);
  _statusEdit->setVisible(true);

  _productsEdited = false;

  if (auto list = qobject_cast<EditableList*>(_productWidget->content()))
  {
    for (auto&& item : *list)
    {
      if (auto widget = qobject_cast<EditableWidget*>(item))
      {
        widget->unlockEdit();
      }
      else
      {
        // Почему-то там не то, что ожидалось
        assert(false);
      }
    }
  }
  else
  {
    // Почему-то там не то, что ожидалось
    assert(false);
  }

  _idEdit->setText(_idLabel->text());
  _operIdEdit->setText(_operIdLabel->text());
  _custIdEdit->setText(_custIdLabel->text());

  _statusEdit->setCurrentText(_statusLabel->text());
}


void OrderWidget::onViewMode(bool reset)
{
  _idLabel->setVisible(true);
  _operIdLabel->setVisible(true);
  _custIdLabel->setVisible(true);
  _statusLabel->setVisible(true);

  _idEdit->setVisible(false);
  _operIdEdit->setVisible(false);
  _custIdEdit->setVisible(false);
  _statusEdit->setVisible(false);

  if (auto list = qobject_cast<EditableList*>(_productWidget->content()))
  {
    for (auto&& item : *list)
    {
      if (auto widget = qobject_cast<EditableWidget*>(item))
      {
        widget->lockEdit();
      }
      else
      {
        // Почему-то там не то, что ожидалось
        assert(false);
      }
    }
  }
  else
  {
    // Почему-то там не то, что ожидалось
    assert(false);
  }

  if (not reset)
  {
    if (_idLabel->text() != _idEdit->text() or _operIdLabel->text() != _operIdEdit->text()
        or _custIdLabel->text() != _custIdEdit->text() or _statusLabel->text() != _statusEdit->currentText()
        or _productsEdited)
    {
      emit dataChanged(_idLabel->text(),
                       _idEdit->text(),
                       _operIdEdit->text(),
                       _custIdEdit->text(),
                       makeList(),
                       statusFromString(_statusEdit->currentText()));

      _idLabel->setText(_idEdit->text());
      _operIdLabel->setText(_operIdEdit->text());
      _custIdLabel->setText(_custIdEdit->text());
      _statusLabel->setText(_statusEdit->currentText());
    }
  }
}


Order::Status OrderWidget::statusFromString(const QString& string)
{
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


void OrderWidget::onInnerDataChanged(QString oldCode, QString newCode, int)
{
  if (oldCode != newCode)
  {
    emit productIdChanged(oldCode, newCode);
    _productsEdited = true;
  }
}
