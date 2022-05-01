#include "ProductCountWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>


namespace
{
constexpr int countMinValue = 0;
constexpr int countMaxValue = 1'000'000'000;
}


ProductCountWidget::ProductCountWidget(const QString& code, const QString& desc, int count) : EditableWidget {nullptr}
{
  _codeLabel = new QLabel(code);
  _codeEdit = new QLineEdit;

  _descLabel = new QLabel(desc);

  _countLabel = new QLabel(QString::number(count));
  _countEdit = new QSpinBox;

  _codeEdit->setVisible(false);
  _countEdit->setVisible(false);
  _countEdit->setRange(countMinValue, countMaxValue);

  auto layout = new QHBoxLayout;
  layout->addWidget(_codeLabel, 1);
  layout->addWidget(_codeEdit, 1);
  layout->addWidget(_descLabel, 1);
  layout->addWidget(_countLabel, 1);
  layout->addWidget(_countEdit, 1);
  contentWidget()->setLayout(layout);
}


void ProductCountWidget::setCount(int count)
{
  count = std::max(count, countMinValue);
  count = std::min(count, countMaxValue);

  _countLabel->setText(QString::number(count));
  _countEdit->setValue(count);
}


int ProductCountWidget::count() const
{
  return _countLabel->text().toInt();
}


void ProductCountWidget::setData(const QString& code, const QString& desc)
{
  _codeLabel->setText(code);
  _codeEdit->setText(code);

  _descLabel->setText(desc);
}


std::tuple<QString, QString> ProductCountWidget::data() const
{
  return {_codeLabel->text(), _descLabel->text()};
}


void ProductCountWidget::onEditMode()
{
  _codeLabel->setVisible(false);
  _countLabel->setVisible(false);

  _codeEdit->setVisible(true);
  _countEdit->setVisible(true);

  _codeEdit->setText(_codeLabel->text());
  _countEdit->setValue(_countLabel->text().toInt());
}


void ProductCountWidget::onViewMode(bool reset)
{
  _codeLabel->setVisible(true);
  _countLabel->setVisible(true);

  _codeEdit->setVisible(false);
  _countEdit->setVisible(false);

  if (not reset)
  {
    if (_codeLabel->text() != _codeEdit->text() or _countEdit->value() != _countLabel->text().toInt())
    {
      emit dataChanged(_codeLabel->text(), _codeEdit->text(), _countEdit->value());

      _codeLabel->setText(_codeEdit->text());
      _countLabel->setText(QString::number(_countEdit->value()));
    }
  }
}
