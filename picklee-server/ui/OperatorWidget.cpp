#include "OperatorWidget.hpp"

#include <QDateEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


namespace
{
constexpr int idWidgetSize = 50;
}


const QString OperatorWidget::dateFormat = "dd.MM.yyyy";


OperatorWidget::OperatorWidget(
    const QString& id, const QString& firstName, const QString& lastName, const QString& patronymic, const QDate& date)
    : EditableWidget {nullptr}
{
  _idLabel = new QLabel(id);
  _idEdit = new QLineEdit;

  _firstNameLabel = new QLabel(firstName);
  _firstNameEdit = new QLineEdit;

  _lastNameLabel = new QLabel(lastName);
  _lastNameEdit = new QLineEdit;

  _patronymicLabel = new QLabel(patronymic);
  _patronymicEdit = new QLineEdit;

  _dateLabel = new QLabel(date.toString(dateFormat));
  _dateEdit = new QDateEdit;

  _idLabel->setFixedWidth(idWidgetSize);
  _idEdit->setFixedWidth(idWidgetSize);

  _idEdit->setVisible(false);
  _firstNameEdit->setVisible(false);
  _lastNameEdit->setVisible(false);
  _patronymicEdit->setVisible(false);
  _dateEdit->setVisible(false);

  auto layout = new QHBoxLayout;
  layout->addWidget(_idLabel, 0);
  layout->addWidget(_idEdit, 0);
  layout->addStretch(1);
  layout->addWidget(_firstNameLabel, 0);
  layout->addWidget(_firstNameEdit, 0);
  layout->addSpacing(5);
  layout->addWidget(_lastNameLabel, 0);
  layout->addWidget(_lastNameEdit, 0);
  layout->addSpacing(5);
  layout->addWidget(_patronymicLabel, 0);
  layout->addWidget(_patronymicEdit, 0);
  layout->addSpacing(5);
  layout->addStretch(1);
  layout->addWidget(_dateLabel, 0);
  layout->addWidget(_dateEdit, 0);

  contentWidget()->setLayout(layout);
}


std::tuple<QString, QString, QString, QString, QDate> OperatorWidget::data() const
{
  return {_idLabel->text(),
          _firstNameLabel->text(),
          _lastNameLabel->text(),
          _patronymicLabel->text(),
          QDate::fromString(_dateLabel->text(), dateFormat)};
}


void OperatorWidget::setData(
    const QString& id, const QString& firstName, const QString& lastName, const QString& patronymic, const QDate& date)
{
  _idLabel->setText(id);
  _idEdit->setText(id);

  _firstNameLabel->setText(firstName);
  _firstNameEdit->setText(firstName);

  _lastNameLabel->setText(lastName);
  _lastNameEdit->setText(lastName);

  _patronymicLabel->setText(patronymic);
  _patronymicEdit->setText(patronymic);

  _dateLabel->setText(date.toString(dateFormat));
  _dateEdit->setDate(date);
}


void OperatorWidget::onEditMode()
{
  _idEdit->setText(_idLabel->text());
  _idLabel->setVisible(false);
  _idEdit->setVisible(true);

  _firstNameEdit->setText(_firstNameLabel->text());
  _firstNameLabel->setVisible(false);
  _firstNameEdit->setVisible(true);

  _lastNameEdit->setText(_lastNameLabel->text());
  _lastNameLabel->setVisible(false);
  _lastNameEdit->setVisible(true);

  _patronymicEdit->setText(_patronymicLabel->text());
  _patronymicLabel->setVisible(false);
  _patronymicEdit->setVisible(true);

  _dateEdit->setDate(QDate::fromString(_dateLabel->text(), dateFormat));
  _dateLabel->setVisible(false);
  _dateEdit->setVisible(true);
}


void OperatorWidget::onViewMode(bool reset)
{
  _idLabel->setVisible(true);
  _idEdit->setVisible(false);

  _firstNameLabel->setVisible(true);
  _firstNameEdit->setVisible(false);

  _lastNameLabel->setVisible(true);
  _lastNameEdit->setVisible(false);

  _patronymicLabel->setVisible(true);
  _patronymicEdit->setVisible(false);

  _dateLabel->setVisible(true);
  _dateEdit->setVisible(false);

  if (not reset)
  {
    if (_idEdit->text().isEmpty())
    {
      _idEdit->setText(_idLabel->text());
    }

    if (_idLabel->text() != _idEdit->text() or _firstNameLabel->text() != _firstNameEdit->text()
        or _lastNameLabel->text() != _lastNameEdit->text() or _patronymicLabel->text() != _patronymicEdit->text()
        or _dateLabel->text() != _dateEdit->date().toString(dateFormat))
    {
      emit dataChanged(_idLabel->text(),
                       _idEdit->text(),
                       _firstNameEdit->text(),
                       _lastNameEdit->text(),
                       _patronymicEdit->text(),
                       _dateEdit->date());

      _idLabel->setText(_idEdit->text());
      _firstNameLabel->setText(_firstNameEdit->text());
      _lastNameLabel->setText(_lastNameEdit->text());
      _patronymicLabel->setText(_patronymicEdit->text());
      _dateLabel->setText(_dateEdit->date().toString(dateFormat));
    }
  }
}
