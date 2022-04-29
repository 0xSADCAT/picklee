#pragma once

#include <QWidget>


class QLabel;
class QLineEdit;
class QPushButton;
class DescriptionMainWidget;


class DescriptionInfoWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit DescriptionInfoWidget(QWidget* parent = nullptr);

  void setData(const QString& id, const QString& description);

  void connectTo(DescriptionMainWidget* widget);

private:
  DescriptionMainWidget* _mainWidget = nullptr;

  QLabel* _idLabel = nullptr;
  QLineEdit* _idEdit = nullptr;

  QLabel* _descLabel = nullptr;
  QLineEdit* _descEdit = nullptr;

  QPushButton* _editButton = nullptr;
  QPushButton* _okButton = nullptr;
  QPushButton* _cancelButton = nullptr;

  void setEditMode();
  void setViewMode(bool cancel);

private slots:
  void onEditButtonClicked();
  void onOkButtonClicked();
  void onCancelButtonClicked();
};
