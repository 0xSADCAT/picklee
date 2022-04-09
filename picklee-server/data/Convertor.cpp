#include "Convertor.hpp"

#include <cassert>


JsonConvertor::JsonConvertor(const QString indentType)
    : _indentType(indentType)
{
    _buffer.push_back("{\n");
}


void JsonConvertor::beginBlock(const QString& blockName)
{
    addIndent();
    ++_indent;

    _buffer.push_back(blockName + " {\n");
}


void JsonConvertor::endBlock(const QString&)
{
    assert(_indent > 1);

    --_indent;
    addIndent();
    _buffer.push_back("}\n");
}


void JsonConvertor::field(const QString& fieldName, const QString& fieldData)
{
    addIndent();
    _buffer.push_back("\"" + fieldName + "\": \"" + fieldData + "\",\n");
}


QString JsonConvertor::result()
{
    QString result;

    for (auto&& str : _buffer) {
        result += str;
    }

    result += "}\n";

    return result;
}


void JsonConvertor::clear()
{
    _buffer.clear();
    _buffer.push_back("{\n");
    _indent = 1;
}


void JsonConvertor::addIndent()
{
    for (int i = 0; i < _indent; ++i) {
        _buffer.push_back(_indentType);
    }
}
