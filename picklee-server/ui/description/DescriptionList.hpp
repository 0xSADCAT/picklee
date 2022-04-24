#pragma once

#include <QWidget>


class QVBoxLayout;
class Description;


class DescriptionList : public QWidget
{
  Q_OBJECT;

public:
  explicit DescriptionList(QWidget* parent = nullptr);

  void removeByCode(const QString& code);
  void clear();

  void add(const QString& code, const QString& desc);

  void editCode(const QString& oldCode, const QString& newCode);
  void editDesc(const QString& code, const QString& newDesc);

signals:
  void codeChanged(const QString& oldCode, const QString& newCode);
  void descriptionChanged(const QString& code, const QString& description);

private:
  QVBoxLayout* _list = nullptr;
};
