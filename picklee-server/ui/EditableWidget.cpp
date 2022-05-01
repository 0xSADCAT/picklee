#include "EditableWidget.hpp"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>


EditableWidget::EditableWidget(QWidget* parent) : QFrame {parent}
{
  _editButton = new QPushButton("Редактировать");
  _okButton = new QPushButton(style()->standardIcon(QStyle::SP_DialogOkButton), "Ок");
  _cancelButton = new QPushButton(style()->standardIcon(QStyle::SP_DialogCancelButton), "Отмена");

  connect(_editButton, &QPushButton::clicked, this, &EditableWidget::onEditClicked);
  connect(_okButton, &QPushButton::clicked, this, &EditableWidget::onOkClicked);
  connect(_cancelButton, &QPushButton::clicked, this, &EditableWidget::onCancelClicked);

  QHBoxLayout* buttons = new QHBoxLayout;
  buttons->addStretch(1);
  buttons->addWidget(_okButton, 0);
  buttons->addSpacing(15);
  buttons->addWidget(_cancelButton, 0);
  buttons->addWidget(_editButton, 0);

  buttons->setSpacing(0);
  buttons->setContentsMargins(0, 0, 0, 0);

  _content = new QWidget;

  auto mainLayout = new QVBoxLayout;
  mainLayout->addWidget(_content);
  mainLayout->addLayout(buttons);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  setStyleSheet("QFrame:hover { background-color: #fbe5cf; }");

  onStateChanged();
}


EditableWidget::State EditableWidget::state() const
{
  return _state;
}

void EditableWidget::setViewMode(bool reset)
{
  if (_state != State::View)
  {
    _state = State::View;
    onStateChanged();
    onViewMode(reset);
  }
}


void EditableWidget::select()
{
  if (_state == State::View and not _editLocked)
  {
    _state = State::Selected;
    onStateChanged();
  }
}


void EditableWidget::lockEdit()
{
  _editLocked = true;
  setViewMode(true);
}


void EditableWidget::unlockEdit()
{
  _editLocked = false;
}


bool EditableWidget::isEditLocked() const
{
  return _editLocked;
}


void EditableWidget::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    if (_state == State::View and not _editLocked)
    {
      _state = State::Selected;
      onStateChanged();
      emit selected();
    }
  }
  else
  {
    QFrame::mousePressEvent(event);
  }
}


QWidget* EditableWidget::contentWidget() const
{
  return _content;
}


void EditableWidget::onStateChanged()
{
  switch (_state)
  {
  case State::View:
    _editButton->setVisible(false);
    _okButton->setVisible(false);
    _cancelButton->setVisible(false);
    break;

  case State::Selected:
    _editButton->setVisible(true);
    _okButton->setVisible(false);
    _cancelButton->setVisible(false);
    break;

  case State::Edit:
    _editButton->setVisible(false);
    _okButton->setVisible(true);
    _cancelButton->setVisible(true);
    break;
  }

  switch (_state)
  {
  case State::View:
    setFrameStyle(QFrame::NoFrame);
    break;

  case State::Selected:
  case State::Edit:
    setFrameStyle(QFrame::WinPanel | QFrame::Plain);
    break;
  }
}


void EditableWidget::onEditClicked()
{
  _state = State::Edit;
  onStateChanged();
  onEditMode();
}


void EditableWidget::onOkClicked()
{
  _state = State::Selected;
  onStateChanged();
  onViewMode(false);
}


void EditableWidget::onCancelClicked()
{
  _state = State::Selected;
  onStateChanged();
  onViewMode(true);
}
