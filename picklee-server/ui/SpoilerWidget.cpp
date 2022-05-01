#include "SpoilerWidget.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>


SpoilerWidget::SpoilerWidget(QWidget* header, QWidget* content)
    : QWidget {nullptr}, _header {header}, _content {content}
{
  assert(header != nullptr);
  assert(content != nullptr);

  _button = new QPushButton;

  QHBoxLayout* topLayout = new QHBoxLayout;
  topLayout->addSpacing(5);
  topLayout->addWidget(header, 1);
  topLayout->addSpacing(5);
  topLayout->addWidget(_button, 0);
  topLayout->addSpacing(5);

  topLayout->setSpacing(0);
  topLayout->setContentsMargins(0, 0, 0, 0);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(topLayout, 0);
  mainLayout->addWidget(content, 1);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  updateButtonIcon();
}


QWidget* SpoilerWidget::header() const
{
  return _header;
}


QWidget* SpoilerWidget::content()
{
  return _content;
}


void SpoilerWidget::showContent()
{
  if (not _content->isVisible())
  {
    _content->setVisible(true);
    updateButtonIcon();
  }
}


void SpoilerWidget::hideContent()
{
  if (_content->isVisible())
  {
    _content->setVisible(false);
    updateButtonIcon();
  }
}


bool SpoilerWidget::isContentVisible() const
{
  return _content->isVisible();
}


void SpoilerWidget::updateButtonIcon()
{
  _button->setIcon(
      style()->standardIcon(isContentVisible() ? QStyle::SP_TitleBarMinButton : QStyle::SP_TitleBarNormalButton));
}


void SpoilerWidget::onButtonClicked()
{
  isContentVisible() ? hideContent() : showContent();
}
