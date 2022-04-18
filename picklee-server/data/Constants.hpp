#pragma once

#include <string_view>


static constexpr std::wstring_view dateTimeFormat = L"dd-MM-yy.hh:mm:ss";


/// Имена полей данных
namespace fn
{
constexpr std::wstring_view id = L"id";
constexpr std::wstring_view operId = L"operId";
constexpr std::wstring_view customerId = L"customerId";
constexpr std::wstring_view status = L"status";
constexpr std::wstring_view firstName = L"firstName";
constexpr std::wstring_view lastName = L"lastName";
constexpr std::wstring_view patronymic = L"patronymic";
constexpr std::wstring_view description = L"description";
constexpr std::wstring_view count = L"count";
constexpr std::wstring_view priority = L"priority";
}


/// Ошибки
namespace err
{
constexpr std::wstring_view input = L"Invalid string";
constexpr std::wstring_view operatorData = L"Invalid operator data";
constexpr std::wstring_view customerData = L"Invalid customer data";
constexpr std::wstring_view warehouseData = L"Invalid warehouse data";
constexpr std::wstring_view orderData = L"Invalid order data";
constexpr std::wstring_view productDescriptionData = L"Invalid product description data";
constexpr std::wstring_view productCountData = L"Invalid product count data";
constexpr std::wstring_view date = L"Invalid date format";
constexpr std::wstring_view time = L"Invalid time format";
constexpr std::wstring_view dateTime = L"Invalid date-time format";
constexpr std::wstring_view unexpectedEOF = L"Unexpected end of file";
constexpr std::wstring_view fileNotFound = L"File not found";
constexpr std::wstring_view permissionDenied = L"Permission denied";
constexpr std::wstring_view alreadyExists = L"Id already exists";
}
