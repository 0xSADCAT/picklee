#pragma once

#include <QVBoxLayout>
#include <QWidget>


class TabPanel : public QWidget
{
  Q_OBJECT;

public:
  explicit TabPanel(QWidget* parent = nullptr);

  void addTopWidget(QWidget* widget);
  void addBottomWidget(QWidget* widget);

private:
  QVBoxLayout* _top = nullptr;
  QVBoxLayout* _bottom = nullptr;
};
