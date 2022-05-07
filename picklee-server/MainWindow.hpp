#pragma once

#include "ui/EditableList.hpp"
#include "ui/I_ProductDescriptionPresenter.hpp"

#include <QtWidgets>


class MainWindow : public QWidget, public I_ProductDescriptionPresenter
{
  Q_OBJECT;

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  // I_ProductDescriptionPresenter interface
public:
  std::optional<std::wstring> descSelected() const noexcept override;
  void selectDesc(const std::wstring& code) noexcept override;
  void addDesc(const std::wstring& code, const std::wstring& desc) noexcept override;
  void editDesc(const std::wstring& code, const std::wstring& newCode, const std::wstring& desc) noexcept override;
  void removeDesc(const std::wstring& code) noexcept override;
  void setDescChangeHandler(
      std::function<void(const std::wstring&, const std::wstring&, const std::wstring&)> handler) noexcept override;

private:
  EditableList* _descList = nullptr;

  std::function<void(const std::wstring&, const std::wstring&, const std::wstring&)> _descChangeHandler;

private slots:
  void onProductDescriptionChanged(QString oldId, QString newId, QString desc);
};
