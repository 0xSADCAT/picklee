#pragma once

#include <QSettings>
#include <string_view>


namespace settings
{
QSettings* get();
void del();

constexpr char windowSize[] = "window/size";
constexpr char windowPos[] = "window/position";
constexpr char splitterPos[] = "window/splitter";
}
