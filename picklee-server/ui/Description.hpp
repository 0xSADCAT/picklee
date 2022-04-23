#pragma once

#include <QWidget>


class EditableLabel;


class Description : public QWidget
{
  Q_OBJECT;

public:
  explicit Description(QWidget* parent = nullptr);

  void loadData(const QString& code, const QString& description);

signals:
  void clicked();
  void codeChanged(const QString& code);
  void descChanged(const QString& desc);

protected:
  void mousePressEvent(QMouseEvent* event) override;

private:
  EditableLabel* _code;
  EditableLabel* _desc;

  void setViewMode();
};
