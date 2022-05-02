#include "WarehouseWidget.hpp"

#include "EditableList.hpp"
#include "ProductCountWidget.hpp"
#include "SpoilerWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>


namespace
{
constexpr int spinMinValue = -1'000'000;
constexpr int spinMaxValue = 1'000'000;


constexpr auto splice = [](int x) {
  return std::max(std::min(x, spinMaxValue), spinMinValue);
};
}


WarehouseWidget::WarehouseWidget(const QString& id,
                                 const QString& desc,
                                 int priority,
                                 QList<ProductCountWidget*> products)
    : EditableWidget {false}
{
  _idLabel = new QLabel(id);
  _idEdit = new QLineEdit;
  _idEdit->setVisible(false);

  _descLabel = new QLabel(desc);
  _descEdit = new QLineEdit;
  _descEdit->setVisible(false);

  priority = splice(priority);
  _priorityLabel = new QLabel(QString::number(priority));
  _priorityEdit = new QSpinBox;
  _priorityEdit->setRange(spinMinValue, spinMaxValue);
  _priorityEdit->setVisible(false);

  _products = new EditableList(false);
  for (auto&& product : products)
  {
    _products->insert(product);
    product->lockEdit();
  }
  SpoilerWidget* spoiler = new SpoilerWidget(new QLabel("Продукты"), _products);
  spoiler->hideContent();

  auto top = new QHBoxLayout;
  top->addWidget(_idLabel, 1);
  top->addWidget(_idEdit, 1);
  top->addSpacing(5);
  top->addWidget(_priorityLabel, 1);
  top->addWidget(_priorityEdit, 1);
  top->addSpacing(5);
  top->addWidget(_descLabel, 1);
  top->addWidget(_descEdit, 1);

  top->setSpacing(0);
  top->setContentsMargins(0, 0, 0, 0);

  auto main = new QVBoxLayout;
  main->addLayout(top, 0);
  main->addWidget(spoiler, 1);

  main->setSpacing(0);
  main->setContentsMargins(0, 0, 0, 0);

  contentWidget()->setLayout(main);
}


EditableList* WarehouseWidget::products() const
{
  return _products;
}


void WarehouseWidget::addProduct(ProductCountWidget* product)
{
  assert(product);

  connect(product, &ProductCountWidget::dataChanged, this, &WarehouseWidget::onInnerDataChanged);
  _products->insert(product);
}


void WarehouseWidget::setId(const QString& id)
{
  _idLabel->setText(id);
  _idEdit->setText(id);
}


QString WarehouseWidget::id() const
{
  return _idLabel->text();
}


void WarehouseWidget::setDesc(const QString& desc)
{
  _descLabel->setText(desc);
  _descEdit->setText(desc);
}


QString WarehouseWidget::desc() const
{
  return _descLabel->text();
}


void WarehouseWidget::setPriority(int value)
{
  value = splice(value);
  _priorityLabel->setText(QString::number(value));
}


int WarehouseWidget::proirity() const
{
  return _priorityLabel->text().toInt();
}


void WarehouseWidget::onEditMode()
{
  setMode(true);

  _idEdit->setText(_idLabel->text());
  _descEdit->setText(_descLabel->text());
  _priorityEdit->setValue(_priorityLabel->text().toInt());

  _productsEdited = false;
}


void WarehouseWidget::onViewMode(bool reset)
{
  setMode(false);

  if (not reset)
  {
    if (_idLabel->text() != _idEdit->text() or _descLabel->text() != _descEdit->text()
        or _priorityLabel->text() != QString::number(_priorityEdit->value()) or _productsEdited)
    {
      emit dataChanged(_idLabel->text(), _idEdit->text(), _descEdit->text(), _priorityEdit->value(), makeList());

      _idLabel->setText(_idEdit->text());
      _descLabel->setText(_descEdit->text());
      _priorityLabel->setText(QString::number(_priorityEdit->value()));
    }
  }
}


QList<QPair<QString, int>> WarehouseWidget::makeList() const
{
  QList<QPair<QString, int>> result;

  for (auto&& item : *_products)
  {
    if (auto widget = qobject_cast<ProductCountWidget*>(item))
    {
      auto&& [code, unused] = widget->data();
      result << QPair(code, widget->count());
    }
    else
    {
      assert(false);
    }
  }

  return result;
}


void WarehouseWidget::setMode(bool edit)
{
  _idLabel->setVisible(not edit);
  _descLabel->setVisible(not edit);
  _priorityLabel->setVisible(not edit);

  _idEdit->setVisible(edit);
  _descEdit->setVisible(edit);
  _priorityEdit->setVisible(edit);

  for (auto item : *_products)
  {
    if (auto widget = qobject_cast<EditableWidget*>(item))
    {
      edit ? widget->unlockEdit() : widget->lockEdit();
    }
    else
    {
      assert(false);
    }
  }
}


void WarehouseWidget::onInnerDataChanged(QString oldCode, QString newCode, int)
{
  if (oldCode != newCode)
  {
    emit productIdChanged(oldCode, newCode);
    _productsEdited = true;
  }
}
