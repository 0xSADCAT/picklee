#include "LineEditWidget.hpp"

#include <QKeyEvent>


LineEditWidget::LineEditWidget(QWidget* parent) : QLineEdit {parent}
{
}


void LineEditWidget::keyPressEvent(QKeyEvent* event)
{
  if (event)
  {
    switch (event->key())
    {
    case Qt::Key::Key_Return:
    case Qt::Key::Key_Enter:
      emit enterPressed();
      break;

    case Qt::Key::Key_Escape:
      emit escapePressed();
      break;

    default:
      QLineEdit::keyPressEvent(event);
      break;
    }
  }
}


void LineEditWidget::keyReleaseEvent(QKeyEvent* event)
{
  if (event == nullptr)
  {
    QLineEdit::keyPressEvent(event);
  }
  else if (event->key() != Qt::Key::Key_Return)
  {
    QLineEdit::keyPressEvent(event);
  }
}
