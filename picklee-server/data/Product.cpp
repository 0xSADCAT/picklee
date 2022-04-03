#include "Product.hpp"


VendorCode::VendorCode(const QString& code)
    : _str(code)
{
}


QString VendorCode::str() const
{
    return _str;
}


bool operator==(const VendorCode& left, const VendorCode& right)
{
    return left.str() == right.str();
}


bool operator!=(const VendorCode& left, const VendorCode& right)
{
    return left.str() != right.str();
}


ProductDescription::ProductDescription(const VendorCode& code, const QString& description)
    : _code(code),
      _description(description)
{
}


const VendorCode& ProductDescription::code() const
{
    return _code;
}


void ProductDescription::setCode(const VendorCode& newCode)
{
    _code = newCode;
}


const QString& ProductDescription::description() const
{
    return _description;
}


void ProductDescription::setDescription(const QString& newDescription)
{
    _description = newDescription;
}


ProductCount::ProductCount(const VendorCode& code, int count)
    : _code(code),
      _count(count)
{
}


const VendorCode& ProductCount::code() const
{
    return _code;
}


void ProductCount::setCode(const VendorCode& newCode)
{
    _code = newCode;
}


int ProductCount::count() const
{
    return _count;
}


void ProductCount::setCount(int newCount)
{
    _count = newCount;
}


int& ProductCount::countRef()
{
    return _count;
}
