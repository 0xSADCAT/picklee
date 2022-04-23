#include "CodeEdit.hpp"

#include <QKeyEvent>


CodeEdit::CodeEdit(QWidget* parent) : QLineEdit {parent}
{
}


void CodeEdit::keyPressEvent(QKeyEvent* event)
{
  if (event)
  {
    if (event->key() == Qt::Key::Key_Return)
    {
      emit enterPressed();
    }
    else if (event->key() == Qt::Key::Key_Escape)
    {
      emit escapePressed();
    }
    else
    {
      QLineEdit::keyPressEvent(event);
    }
  }
}


void CodeEdit::keyReleaseEvent(QKeyEvent* event)
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
