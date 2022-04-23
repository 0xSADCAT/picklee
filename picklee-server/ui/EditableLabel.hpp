#pragma once

#include <QWidget>


class LineEditWidget;
class QLabel;


class EditableLabel : public QWidget
{
  Q_OBJECT;

public:
  explicit EditableLabel(QWidget* parent = nullptr);

  void setText(const QString& text);
  QString text() const;

  bool isEditMode() const;
  void setEditMode(bool edit);

signals:
  void valueChanged(const QString& text);

protected:
  void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
  LineEditWidget* _edit = nullptr;
  QLabel* _label = nullptr;

  void setViewMode();

private slots:
  void onEditEnterPressed();
  void onEditEscapePressed();
};
