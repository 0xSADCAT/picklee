#include "ProductDescriptionWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


ProductDescriptionWidget::ProductDescriptionWidget(const QString& id, const QString& desc) : EditableWidget {false}
{
  _idLabel = new QLabel(id);
  _descLabel = new QLabel(desc);

  _idEdit = new QLineEdit;
  _idEdit->setVisible(false);
  _descEdit = new QLineEdit;
  _descEdit->setVisible(false);

  auto layout = new QHBoxLayout;
  layout->addWidget(_idLabel, 1);
  layout->addWidget(_idEdit, 1);
  layout->addWidget(_descLabel, 1);
  layout->addWidget(_descEdit, 1);

  contentWidget()->setLayout(layout);
}


std::pair<QString, QString> ProductDescriptionWidget::data() const
{
  return {_idLabel->text(), _descLabel->text()};
}


void ProductDescriptionWidget::setData(const QString& id, const QString& desc)
{
  _idLabel->setText(id);
  _idEdit->setText(id);

  _descLabel->setText(desc);
  _descEdit->setText(desc);
}


void ProductDescriptionWidget::onEditMode()
{
  _idEdit->setText(_idLabel->text());
  _idEdit->setVisible(true);
  _idLabel->setVisible(false);

  _descEdit->setText(_descLabel->text());
  _descEdit->setVisible(true);
  _descLabel->setVisible(false);
}


void ProductDescriptionWidget::onViewMode(bool reset)
{
  _idEdit->setVisible(false);
  _idLabel->setVisible(true);

  _descEdit->setVisible(false);
  _descLabel->setVisible(true);

  if (not reset)
  {
    if (_idEdit->text().isEmpty())
    {
      _idEdit->setText(_idLabel->text());
    }

    if (_idEdit->text() != _idLabel->text() or _descEdit->text() != _descLabel->text())
    {
      emit dataChanged(_idLabel->text(), _idEdit->text(), _descEdit->text());

      _idLabel->setText(_idEdit->text());
      _descLabel->setText(_descEdit->text());
    }
  }
}
