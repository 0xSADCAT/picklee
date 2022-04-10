#pragma once

#include <string_view>


static constexpr std::wstring_view dateTimeFormat = L"dd.MM.yy-hh:mm:ss";


/// Имена полей данных
namespace fn {
static constexpr std::wstring_view id = L"id";
static constexpr std::wstring_view operId = L"operId";
static constexpr std::wstring_view customerId = L"customerId";
static constexpr std::wstring_view status = L"status";
static constexpr std::wstring_view firstName = L"firstName";
static constexpr std::wstring_view lastName = L"lastName";
static constexpr std::wstring_view patronymic = L"patronymic";
static constexpr std::wstring_view description = L"description";
static constexpr std::wstring_view count = L"count";
static constexpr std::wstring_view priority = L"priority";
}
