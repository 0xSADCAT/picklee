#pragma once

#include <QWidget>


class QVBoxLayout;
class EditableWidget;


class EditableList : public QWidget
{
  Q_OBJECT;

public:
  explicit EditableList(QWidget* parent = nullptr);

  void insert(EditableWidget* widget);
  void remove(EditableWidget* widget);
  void clear(bool deleteWidgets = true);

  QList<EditableWidget*>::Iterator begin();
  QList<EditableWidget*>::Iterator end();

  EditableWidget* selected() const;

  void setSelected(EditableWidget* newSelected);

private:
  QList<EditableWidget*> _widgets;
  QVBoxLayout* _layout;
  EditableWidget* _selected = nullptr;

private slots:
  void onWidgetSelected();
};
