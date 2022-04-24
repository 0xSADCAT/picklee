#pragma once

#include <QVBoxLayout>
#include <QWidget>


class ContainerWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit ContainerWidget(QWidget* parent = nullptr);

  void setWidgets(QList<QWidget*> widgets);

  QWidget* current() const;

  void showWidget(QWidget* widget);
  void showWidget(int number);

private:
  QWidget* _current = nullptr;
  QList<QWidget*> _widgets;
  QVBoxLayout* _layout = nullptr;
};
