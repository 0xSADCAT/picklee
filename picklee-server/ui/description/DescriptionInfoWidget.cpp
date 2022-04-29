#include "DescriptionInfoWidget.hpp"

#include "DescriptionMainWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>


DescriptionInfoWidget::DescriptionInfoWidget(QWidget *parent)
    : QWidget{parent}
{
  _idLabel = new QLabel;
  _idEdit = new QLineEdit;
  _idEdit->setVisible(false);

  _descLabel = new QLabel;
  _descEdit = new QLineEdit;
  _descEdit->setVisible(false);

  _editButton = new QPushButton("Редактировать");
  _okButton = new QPushButton("Ок");
  _okButton->setVisible(false);
  _cancelButton = new QPushButton("Отмена");
  _cancelButton->setVisible(false);

  QHBoxLayout* id = new QHBoxLayout;
  id->addWidget(new QLabel("Id: "));
  id->addWidget(_idLabel, 1);
  id->addWidget(_idEdit, 1);

  QHBoxLayout* desc = new QHBoxLayout;
  desc->addWidget(new QLabel("Описание: "));
  desc->addWidget(_descLabel, 1);
  desc->addWidget(_descEdit, 1);

  QHBoxLayout* buttons = new QHBoxLayout;
  buttons->addStretch(1);
  buttons->addWidget(_editButton, 0);
  buttons->addWidget(_okButton, 0);
  buttons->addSpacing(10);
  buttons->addWidget(_cancelButton, 0);

  QVBoxLayout* main = new QVBoxLayout;
  main->addLayout(id, 0);
  main->addLayout(desc, 0);
  main->addLayout(buttons, 0);
  main->addStretch(1);

  setLayout(main);

  connect(_editButton, &QPushButton::clicked, this, &DescriptionInfoWidget::onEditButtonClicked);
  connect(_okButton, &QPushButton::clicked, this, &DescriptionInfoWidget::onOkButtonClicked);
  connect(_cancelButton, &QPushButton::clicked, this, &DescriptionInfoWidget::onCancelButtonClicked);
}


void DescriptionInfoWidget::setData(const QString& id, const QString& description)
{
  if (_idLabel->text() != id and _descLabel->text() != description)
  {
    setViewMode(true);
    _idLabel->setText(id);
    _descLabel->setText(description);
  }
}


void DescriptionInfoWidget::connectTo(DescriptionMainWidget* widget)
{
  assert(widget != nullptr);
  assert(_mainWidget == nullptr);

  _mainWidget = widget;
}


void DescriptionInfoWidget::setEditMode()
{
  _idEdit->setText(_idLabel->text());
  _descEdit->setText(_descLabel->text());

  _idLabel->setVisible(false);
  _idEdit->setVisible(true);

  _descLabel->setVisible(false);
  _descEdit->setVisible(true);

  _editButton->setVisible(false);
  _okButton->setVisible(true);
  _cancelButton->setVisible(true);
}


void DescriptionInfoWidget::setViewMode(bool cancel)
{
  if (not cancel)
  {
    bool idChanged = not _idEdit->text().isEmpty() and _idLabel->text() != _idEdit->text();
    bool descChanged = not _descEdit->text().isEmpty() and _descLabel->text() != _descEdit->text();

    if (idChanged and descChanged)
    {
      _mainWidget->editData(_idLabel->text(), _idEdit->text(), _descEdit->text());
      _idLabel->setText(_idEdit->text());
      _descLabel->setText(_descEdit->text());
    }
    else if (idChanged)
    {
      _mainWidget->editId(_idLabel->text(), _idEdit->text());
      _idLabel->setText(_idEdit->text());
    }
    else if (descChanged)
    {
      _mainWidget->editDescription(_idLabel->text(), _descEdit->text());
      _descLabel->setText(_descEdit->text());
    }
  }

  _idLabel->setVisible(true);
  _idEdit->setVisible(false);

  _descLabel->setVisible(true);
  _descEdit->setVisible(false);

  _editButton->setVisible(true);
  _okButton->setVisible(false);
  _cancelButton->setVisible(false);
}


void DescriptionInfoWidget::onEditButtonClicked()
{
  if (_idLabel->text().isEmpty())
  {
    return;
  }

  setEditMode();
}


void DescriptionInfoWidget::onOkButtonClicked()
{
  setViewMode(false);
}


void DescriptionInfoWidget::onCancelButtonClicked()
{
  setViewMode(true);
}
