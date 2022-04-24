#pragma once

#include <QWidget>


class QLineEdit;
class QVBoxLayout;
class QLabel;

class DescriptionInfoWidget;


class DescriptionMainWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit DescriptionMainWidget(QWidget* parent = nullptr);

  void setInfoWidget(DescriptionInfoWidget* widget);

  void addDescription(const QString& id, const QString& description);
  void removeDescription(const QString& id);
  void editData(const QString& id, const QString& newId, const QString& newDescription);
  void editDescription(const QString& id, const QString& newDescription);
  void editId(const QString& id, const QString& newId);

signals:
  void descriptionChanged(const QString& id, const QString& newDescription);
  void idChanged(const QString& oldId, const QString& newId);
  void elementDeleted(const QString& id);

private:
  DescriptionInfoWidget* _infoWidget = nullptr;
  QList<QPair<QString, QWidget*>> _descriptions;
  QVBoxLayout* _widgetsLayout = nullptr;

private slots:
  void onEditDone(const QString& oldId, const QString& newId, const QString& newDescription);
  void onDescriptionDeleted(const QString& id);
  void onElementClicked();
};
