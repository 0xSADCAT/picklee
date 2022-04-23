#include "Description.hpp"

#include "EditableLabel.hpp"

#include <QHBoxLayout>
#include <QMouseEvent>


Description::Description(QWidget* parent) : QWidget {parent}
{
  _code = new EditableLabel;
  _desc = new EditableLabel;

  QHBoxLayout* lay = new QHBoxLayout;
  lay->addWidget(_code);
  lay->addWidget(_desc);
  setLayout(lay);

  connect(_code, &EditableLabel::valueChanged, this, &Description::codeChanged);
  connect(_desc, &EditableLabel::valueChanged, this, &Description::descChanged);
}


void Description::loadData(const QString& code, const QString& description)
{
  setViewMode();
  _code->setText(code);
  _desc->setText(description);
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
