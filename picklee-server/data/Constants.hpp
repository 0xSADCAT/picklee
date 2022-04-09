#pragma once

#include <QString>


Q_GLOBAL_STATIC_WITH_ARGS(const QString, dateTimeFormat, ("dd.MM.yy-hh:mm:ss"));


/// Имена полей данных
namespace fn {
static constexpr char id[] = "id";
static constexpr char operId[] = "operId";
static constexpr char customerId[] = "customerId";
static constexpr char status[] = "status";
static constexpr char firstName[] = "firstName";
static constexpr char lastName[] = "lastName";
static constexpr char patronymic[] = "patronymic";
static constexpr char description[] = "description";
static constexpr char count[] = "count";
static constexpr char priority[] = "priority";
}
