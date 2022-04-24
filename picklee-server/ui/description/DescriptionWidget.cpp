#include "DescriptionWidget.hpp"

#include <QHBoxLayout>
#include <QMouseEvent>


DescriptionWidget::DescriptionWidget(const QString& id, const QString& desc) : QWidget {nullptr}
{
  assert(not id.isEmpty());

  _idLabel = new QLabel(id);
  _descLabel = new QLabel(desc);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(_idLabel, 1);
  mainLayout->addWidget(_descLabel, 1);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


QString DescriptionWidget::id() const
{
  return _idLabel->text();
}


QString DescriptionWidget::desc() const
{
  return _descLabel->text();
}


void DescriptionWidget::setId(const QString& value)
{
  assert(not value.isEmpty());

  _idLabel->setText(value);
}


void DescriptionWidget::setDesc(const QString& value)
{
  _descLabel->setText(value);
}


void DescriptionWidget::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    emit clicked();
  }
  else
  {
    QWidget::mousePressEvent(event);
  }
}
