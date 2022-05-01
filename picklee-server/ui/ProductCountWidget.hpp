#pragma once

#include "EditableWidget.hpp"


class QLabel;
class QLineEdit;
class QSpinBox;


class ProductCountWidget : public EditableWidget
{
  Q_OBJECT;

public:
  explicit ProductCountWidget(const QString& code, const QString& desc, int count);

  void setCount(int count);
  int count() const;

  void setData(const QString& code, const QString& desc);
  std::tuple<QString, QString> data() const;

signals:
  void dataChanged(QString oldCode, QString newCode, int count);

protected:
  void onEditMode() override;
  void onViewMode(bool reset) override;

private:
  QLabel* _codeLabel;
  QLineEdit* _codeEdit;

  QLabel* _descLabel;

  QLabel* _countLabel;
  QSpinBox* _countEdit;
};
