#pragma once

#include <QWidget>


class QPushButton;


class SpoilerWidget : public QWidget
{
  Q_OBJECT;

public:
  explicit SpoilerWidget(QWidget* header, QWidget* content);

  QWidget* header() const;

  QWidget* content();

  void showContent();
  void hideContent();
  bool isContentVisible() const;

signals:
  void contentVisibleChanged(bool visible);

private:
  QWidget* _header;
  QWidget* _content;
  QPushButton* _button;

  void updateButtonIcon();

private slots:
  void onButtonClicked();
};
