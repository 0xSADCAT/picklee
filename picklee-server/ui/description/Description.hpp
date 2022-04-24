#pragma once

#include <QFrame>


class EditableLabel;


class Description : public QFrame
{
  Q_OBJECT;

public:
  explicit Description(QWidget* parent = nullptr);

  void loadData(const QString& code, const QString& description);

  QString code() const;
  QString desc() const;

signals:
  void clicked();
  void codeChanged(const QString& oldCode, const QString& newCode);
  void descChanged(const QString& code, const QString& desc);

protected:
  void mousePressEvent(QMouseEvent* event) override;

private:
  EditableLabel* _code;
  EditableLabel* _desc;

  void setViewMode();

private slots:
  void onCodeValueChanged(const QString& newCode, const QString& oldCode);
  void onDescriptionValueChanged(const QString& newDescription, const QString&);
};
