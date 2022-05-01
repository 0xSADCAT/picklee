#pragma once

#include "../data/Order.hpp"
#include "EditableWidget.hpp"


class QLabel;
class QLineEdit;
class QComboBox;
class ProductCountWidget;
class EditableList;
class SpoilerWidget;


class OrderWidget : public EditableWidget
{
  Q_OBJECT;

public:
  OrderWidget(const QString& newId,
              const QString& operId,
              const QString& custId,
              const QList<ProductCountWidget*>& products,
              Order::Status status);

  void setProducts(QList<ProductCountWidget*> products);
  EditableList* products() const;

  void setStatus(Order::Status status);
  Order::Status status() const;

  void setData(const QString& id, const QString& operId, const QString& custId);
  std::tuple<QString, QString, QString> data() const;

signals:
  void dataChanged(QString oldId,
                   QString newId,
                   QString operId,
                   QString custId,
                   QList<QPair<QString, int>> products,
                   Order::Status status);

protected:
  void onEditMode() override;
  void onViewMode(bool reset) override;

private:
  QLabel* _idLabel;
  QLabel* _operIdLabel;
  QLabel* _custIdLabel;
  SpoilerWidget* _productWidget;
  QLabel* _statusLabel;

  QLineEdit* _idEdit;
  QLineEdit* _operEdit;
  QLineEdit* _custEdit;
  QComboBox* _statusEdit;

  static Order::Status statusFromString(const QString& string);
  QList<QPair<QString, int>> makeList() const;
};
