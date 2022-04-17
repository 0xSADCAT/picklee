#include "JsonParser.hpp"


void JsonParser::parse(const std::wstring& string) noexcept
{
}


std::vector<Order> JsonParser::orders() const noexcept
{
}


std::vector<Operator> JsonParser::operators() const noexcept
{
}


std::vector<Customer> JsonParser::customers() const noexcept
{
}


std::vector<ProductDescription> JsonParser::descriptions() const noexcept
{
}


std::vector<Warehouse> JsonParser::warehouses() const noexcept
{
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Order> > inserter) const noexcept
{
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Operator> > inserter) const noexcept
{
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Customer> > inserter) const noexcept
{
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<ProductDescription> > inserter) const noexcept
{
}


void JsonParser::loadTo(std::back_insert_iterator<std::vector<Warehouse> > inserter) const noexcept
{
}


std::vector<std::pair<std::wstring_view, std::wstring> > JsonParser::errors() const noexcept
{
}


void JsonParser::clear() noexcept
{
}


void JsonParser::pushError(std::wstring_view err, const std::wstring& string) noexcept
{
}


Order JsonParser::parseOrder(const std::wstring& string)
{
}


Operator JsonParser::parseOperator(const std::wstring& string)
{
}


Customer JsonParser::parseCustomer(const std::wstring& string)
{
}


Person JsonParser::parsePerson(const std::wstring& string)
{
}


ProductDescription JsonParser::parseDescription(const std::wstring& string)
{
}


ProductCount JsonParser::parseCount(const std::wstring& string)
{
}


Warehouse JsonParser::parseWarehouse(const std::wstring& string)
{
}
