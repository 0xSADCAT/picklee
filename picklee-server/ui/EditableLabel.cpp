#include "EditableLabel.hpp"

#include "LineEditWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>


EditableLabel::EditableLabel(QWidget* parent) : QWidget {parent}
{
  _edit = new LineEditWidget;
  _label = new QLabel;

  QHBoxLayout* lay = new QHBoxLayout;
  lay->addWidget(_label);
  lay->addWidget(_edit);
  setLayout(lay);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  connect(_edit, &LineEditWidget::enterPressed, this, &EditableLabel::onEditEnterPressed);
  connect(_edit, &LineEditWidget::escapePressed, this, &EditableLabel::onEditEscapePressed);

  _edit->setVisible(false);
}


void EditableLabel::setText(const QString& text)
{
  _edit->setText(text);
  _label->setText(text);
}


QString EditableLabel::text() const
{
  return _label->text();
}


bool EditableLabel::isEditMode() const
{
  return _edit->isVisible();
}


void EditableLabel::setEditMode(bool edit)
{
  if (edit)
  {
    _edit->setText(_label->text());
    _edit->setVisible(edit);
    _label->setVisible(not edit);
  }
  else
  {
    setViewMode();
  }
}


void EditableLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    if (not isEditMode())
    {
      _edit->setText(_label->text());
      _edit->setVisible(true);
      _label->setVisible(false);
    }
  }
  else
  {
    QWidget::mouseDoubleClickEvent(event);
  }
}


void EditableLabel::setViewMode()
{
  if (isEditMode())
  {
    if (_edit->text() != _label->text())
    {
      _label->setText(_edit->text());
      emit valueChanged(_label->text());
    }
  }

  _edit->setVisible(false);
  _label->setVisible(true);
}


void EditableLabel::onEditEnterPressed()
{
  setViewMode();
}


void EditableLabel::onEditEscapePressed()
{
  if (isEditMode())
  {
    _edit->setText(_label->text());
    _label->setVisible(true);
    _edit->setVisible(false);
  }
}
