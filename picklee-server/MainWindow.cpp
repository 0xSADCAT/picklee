#include "MainWindow.hpp"

#include "Logger.hpp"
#include "Settings.hpp"
#include "ui/EditableList.hpp"
#include "ui/ProductCountWidget.hpp"
#include "ui/ProductDescriptionWidget.hpp"
#include "ui/WarehouseWidget.hpp"


MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
  QVariant winSize = settings::get()->value(settings::windowSize);
  QVariant winPos = settings::get()->value(settings::windowPos);
  if (not winSize.isNull() and winSize.isValid() and not winPos.isNull() and winPos.isValid())
  {
    setGeometry(QRect {qvariant_cast<QPoint>(winPos), qvariant_cast<QSize>(winSize)});
  }

  setLayout(new QVBoxLayout);

  _descList = new EditableList;

  layout()->addWidget(_descList);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}


MainWindow::~MainWindow()
{
  settings::get()->setValue(settings::windowPos, pos());
  settings::get()->setValue(settings::windowSize, size());

  settings::del();
}


std::optional<std::wstring> MainWindow::descSelected() const noexcept
{
  std::optional<std::wstring> result = std::nullopt;

  if (auto desc = qobject_cast<ProductDescriptionWidget*>(_descList->selected()))
  {
    auto&& [id, unused] = desc->data();
    result = id.toStdWString();
  }

  return result;
}


void MainWindow::selectDesc(const std::wstring& code) noexcept
{
  QString strId = QString::fromStdWString(code);

  _descList->setSelected(nullptr);

  for (auto&& item : *_descList)
  {
    if (auto desc = qobject_cast<ProductDescriptionWidget*>(item))
    {
      auto&& [id, unused] = desc->data();
      if (id == strId)
      {
        _descList->setSelected(desc);
        break;
      }
    }
    else
    {
      PICKLEE_ASSERT(false);
    }
  }
}


void MainWindow::addDesc(const std::wstring& code, const std::wstring& desc) noexcept
{
  auto widget = new ProductDescriptionWidget(QString::fromStdWString(code), QString::fromStdWString(desc));
  _descList->insert(widget);
  connect(widget, &ProductDescriptionWidget::dataChanged, this, &MainWindow::onProductDescriptionChanged);
}


static constexpr auto findDesc = [](EditableList* list, const std::wstring& id) {
  QString strId = QString::fromStdWString(id);

  auto iter = std::find_if(list->begin(), list->end(), [&strId](EditableWidget* widget) {
    if (auto desc = qobject_cast<ProductDescriptionWidget*>(widget))
    {
      auto&& [id, unused] = desc->data();
      return id == strId;
    }
    else
    {
      PICKLEE_ASSERT(false);
      return false;
    }
  });

  if (iter == list->end())
  {
    return static_cast<ProductDescriptionWidget*>(nullptr);
  }
  else
  {
    return qobject_cast<ProductDescriptionWidget*>(*iter);
  }
};


void MainWindow::editDesc(const std::wstring& code, const std::wstring& newCode, const std::wstring& desc) noexcept
{
  auto widget = findDesc(_descList, code);

  PICKLEE_ASSERT(widget != nullptr);

  widget->setData(QString::fromStdWString(newCode), QString::fromStdWString(desc));
}


void MainWindow::removeDesc(const std::wstring& code) noexcept
{
  auto widget = findDesc(_descList, code);

  PICKLEE_ASSERT(widget != nullptr);

  _descList->remove(widget);
}


void MainWindow::setDescChangeHandler(
    std::function<void(const std::wstring&, const std::wstring&, const std::wstring&)> handler) noexcept
{
  _descChangeHandler = handler;
}


void MainWindow::onProductDescriptionChanged(QString oldId, QString newId, QString desc)
{
  PICKLEE_ASSERT(_descChangeHandler);

  _descChangeHandler(oldId.toStdWString(), newId.toStdWString(), desc.toStdWString());
}
