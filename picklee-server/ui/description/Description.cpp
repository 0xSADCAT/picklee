#include "Description.hpp"

#include "../EditableLabel.hpp"

#include <QHBoxLayout>
#include <QMouseEvent>


Description::Description(QWidget* parent) : QFrame {parent}
{
  _code = new EditableLabel;
  _desc = new EditableLabel;

  QHBoxLayout* lay = new QHBoxLayout;
  lay->addWidget(_code, 1);
  lay->addWidget(_desc, 1);
  setLayout(lay);

  connect(_code, &EditableLabel::valueChanged, this, &Description::onCodeValueChanged);
  connect(_desc, &EditableLabel::valueChanged, this, &Description::onDescriptionValueChanged);

  setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  setFixedHeight(lay->minimumSize().height());
}


void Description::loadData(const QString& code, const QString& description)
{
  setViewMode();
  _code->setText(code);
  _desc->setText(description);
}


QString Description::code() const
{
  return _code->text();
}


QString Description::desc() const
{
  return _desc->text();
}


void Description::mousePressEvent(QMouseEvent* event)
{
  if (event and event->button() == Qt::LeftButton)
  {
    emit clicked();
  }
  else
  {
    QWidget::mousePressEvent(event);
  }
}


void Description::setViewMode()
{
  _code->setEditMode(false);
  _desc->setEditMode(false);
}


void Description::onCodeValueChanged(const QString& newCode, const QString& oldCode)
{
  emit codeChanged(newCode, oldCode);
}


void Description::onDescriptionValueChanged(const QString& newDescription, const QString&)
{
  emit descChanged(_code->text(), newDescription);
}
