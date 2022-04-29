#pragma once

#include <QtWidgets>


class MainWindow : public QWidget
{
  Q_OBJECT;

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
};
