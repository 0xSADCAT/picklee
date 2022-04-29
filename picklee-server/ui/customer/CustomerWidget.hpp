#pragma once

#include <QDate>
#include <QString>
#include <QWidget>


class QLabel;


class CustomerWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit CustomerWidget(QWidget* parent = nullptr);

  void setData(const QString& id,
               const QString& firstName,
               const QString& lastName,
               const QString& patronymic,
               const QDate& date);

  std::tuple<QString, QString, QString, QString, QDate> data();

  void select();
  void unselect();

  bool isSelected() const;

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent* event) override;

private:
  bool _selected = false;

  QLabel* _id = nullptr;
  QLabel* _firstName = nullptr;
  QLabel* _lastName = nullptr;
  QLabel* _patronumic = nullptr;
  QLabel* _date = nullptr;

  const static QString dateFormat;

  void updateStyle();
};
