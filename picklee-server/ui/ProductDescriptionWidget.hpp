#pragma once

#include "EditableWidget.hpp"


class QLabel;
class QLineEdit;


class ProductDescriptionWidget : public EditableWidget
{
  Q_OBJECT;

public:
  ProductDescriptionWidget(const QString& id, const QString& desc);

  std::pair<QString, QString> data() const;
  void setData(const QString& id, const QString& desc);

signals:
  void dataChanged(QString oldId, QString newId, QString desc);

protected:
  void onEditMode() override;
  void onViewMode(bool reset) override;

private:
  QLabel* _idLabel;
  QLabel* _descLabel;

  QLineEdit* _idEdit;
  QLineEdit* _descEdit;
};
