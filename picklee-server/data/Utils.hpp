#pragma once

#include <algorithm>
#include <string>


namespace util::str {
static const auto contains = [](const std::wstring_view& str, const std::wstring_view& substr) {
    return str.find(substr) != str.npos;
};

static const auto startsWith = [](const std::wstring_view& str, const std::wstring_view& prefix) {
    if (str.length() < prefix.length())
        return false;
    return std::equal(str.begin(), str.begin() + prefix.length(), prefix.begin());
};
}
