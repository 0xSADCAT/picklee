#pragma once

#include <QLineEdit>


class LineEditWidget : public QLineEdit
{
  Q_OBJECT;

public:
  explicit LineEditWidget(QWidget* parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

signals:
  void enterPressed();
  void escapePressed();
};
