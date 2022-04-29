#include "CustomerWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>


const QString CustomerWidget::dateFormat = "dd.MM.yyyy";


CustomerWidget::CustomerWidget(QWidget* parent) : QWidget {parent}
{
  _id = new QLabel;
  _firstName = new QLabel;
  _lastName = new QLabel;
  _patronumic = new QLabel;
  _date = new QLabel;

  QHBoxLayout* lay = new QHBoxLayout;
  lay->addWidget(_id, 1);
  lay->addWidget(_firstName, 1);
  lay->addWidget(_lastName, 1);
  lay->addWidget(_patronumic, 1);
  lay->addWidget(_date, 1);
  setLayout(lay);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


void CustomerWidget::setData(
    const QString& id, const QString& firstName, const QString& lastName, const QString& patronymic, const QDate& date)
{
  _id->setText(id);
  _firstName->setText(firstName);
  _lastName->setText(lastName);
  _patronumic->setText(patronymic);
  _date->setText(date.toString(dateFormat));
}


std::tuple<QString, QString, QString, QString, QDate> CustomerWidget::data()
{
  return {_id->text(),
          _firstName->text(),
          _lastName->text(),
          _patronumic->text(),
          QDate::fromString(_date->text(), dateFormat)};
}


void CustomerWidget::select()
{
  if (not _selected)
  {
    _selected = true;
    updateStyle();
  }
}


void CustomerWidget::unselect()
{
  if (_selected)
  {
    _selected = false;
    updateStyle();
  }
}


bool CustomerWidget::isSelected() const
{
  return _selected;
}


void CustomerWidget::mousePressEvent(QMouseEvent* event)
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


void CustomerWidget::updateStyle()
{
  const static QString selectedStyle = "*{background: #d3e8ff;}";
  const static QString unselectedStyle = "";

  setStyleSheet(_selected ? selectedStyle : unselectedStyle);
}
