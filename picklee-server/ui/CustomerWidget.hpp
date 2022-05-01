#pragma once

#include "EditableWidget.hpp"

#include <QDate>


class QLabel;
class QLineEdit;
class QDateEdit;


class CustomerWidget : public EditableWidget
{
  Q_OBJECT;

public:
  CustomerWidget(const QString& id,
                 const QString& firstName,
                 const QString& lastName,
                 const QString& patronymic,
                 const QDate& date);

  std::tuple<QString, QString, QString, QString, QDate> data() const;
  void setData(const QString& id,
               const QString& firstName,
               const QString& lastName,
               const QString& patronymic,
               const QDate& date);

signals:
  void dataChanged(QString oldId, QString newId, QString firstName, QString lastName, QString patronymic, QDate date);

protected:
  void onEditMode() override;
  void onViewMode(bool reset) override;

private:
  QLabel* _idLabel;
  QLineEdit* _idEdit;

  QLabel* _firstNameLabel;
  QLineEdit* _firstNameEdit;

  QLabel* _lastNameLabel;
  QLineEdit* _lastNameEdit;

  QLabel* _patronymicLabel;
  QLineEdit* _patronymicEdit;

  QLabel* _dateLabel;
  QDateEdit* _dateEdit;

  const static QString dateFormat;
};
