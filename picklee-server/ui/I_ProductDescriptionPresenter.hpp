#pragma once

#include <functional>
#include <optional>
#include <string>


class I_ProductDescriptionPresenter
{
public:
  I_ProductDescriptionPresenter() noexcept = default;
  virtual ~I_ProductDescriptionPresenter() noexcept = default;

  virtual std::optional<std::wstring> descSelected() const noexcept = 0;
  virtual void selectDesc(const std::wstring& code) noexcept = 0;

  virtual void addDesc(const std::wstring& code, const std::wstring& desc) noexcept = 0;
  virtual void editDesc(const std::wstring& code, const std::wstring& newCode, const std::wstring& desc) noexcept = 0;
  virtual void removeDesc(const std::wstring& code) noexcept = 0;

  virtual void setDescChangeHandler(
      std::function<void(const std::wstring&, const std::wstring&, const std::wstring&)> handler) noexcept = 0;
};
