#pragma once

#include <QLabel>
#include <QWidget>

class DescriptionWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit DescriptionWidget(const QString& id, const QString& desc);

  QString id() const;
  QString desc() const;

  void setId(const QString& value);
  void setDesc(const QString& value);

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent* event) override;

private:
  QLabel* _idLabel = nullptr;
  QLabel* _descLabel = nullptr;
};
