#pragma once

#include "EditableWidget.hpp"


class QLabel;
class QLineEdit;
class QSpinBox;
class ProductCountWidget;
class EditableList;


class WarehouseWidget : public EditableWidget
{
  Q_OBJECT;

public:
  WarehouseWidget(const QString& id, const QString& desc, int priority, QList<ProductCountWidget*> products);

  EditableList* products() const;
  void addProduct(ProductCountWidget* product);

  void setId(const QString& id);
  QString id() const;

  void setDesc(const QString& desc);
  QString desc() const;

  void setPriority(int value);
  int proirity() const;

signals:
  void dataChanged(QString oldId, QString newId, QString desc, int priority, QList<QPair<QString, int>> products);
  void productIdChanged(QString oldId, QString newId);

protected:
  void onEditMode() override;
  void onViewMode(bool reset) override;

private:
  QLabel* _idLabel;
  QLineEdit* _idEdit;

  QLabel* _descLabel;
  QLineEdit* _descEdit;

  QLabel* _priorityLabel;
  QSpinBox* _priorityEdit;

  EditableList* _products;

  bool _productsEdited = false;

  QList<QPair<QString, int>> makeList() const;
  void setMode(bool edit);

private slots:
  void onInnerDataChanged(QString oldCode, QString newCode, int);
};
