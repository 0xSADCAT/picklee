#pragma once

#include <QFrame>


class QPushButton;
class QHBoxLayout;
class QVBoxLayout;


/// Виджет с возможностью редактирования
class EditableWidget : public QFrame
{
  Q_OBJECT;

public:
  enum class State
  {
    View,
    Selected,
    Edit
  };

  explicit EditableWidget(bool oneLine = false);

  State state() const;
  void setViewMode(bool reset);
  void select();

  void lockEdit();
  void unlockEdit();
  bool isEditLocked() const;

signals:
  void selected();

protected:
  void mousePressEvent(QMouseEvent* event) override;

  QWidget* contentWidget() const;

  virtual void onEditMode() = 0;
  virtual void onViewMode(bool reset) = 0;

private:
  QPushButton* _editButton;
  QPushButton* _okButton;
  QPushButton* _cancelButton;

  QWidget* _content;

  State _state = State::View;

  bool _editLocked = false;

  void onStateChanged();

private slots:
  void onEditClicked();
  void onOkClicked();
  void onCancelClicked();
};
