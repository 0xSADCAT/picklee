#pragma once

#include <QString>


/// Артикул
class VendorCode
{
public:
    VendorCode(const QString& code);

    QString str() const;

private:
    QString _str;
};


bool operator==(const VendorCode& left, const VendorCode& right);
bool operator!=(const VendorCode& left, const VendorCode& right);


/// Пара артикул-описание
class ProductDescription
{
public:
    ProductDescription(const VendorCode& code, const QString& description);

    const VendorCode& code() const;
    void setCode(const VendorCode& newCode);

    const QString& description() const;
    void setDescription(const QString& newDescription);

private:
    VendorCode _code;
    QString _description;
};


/// Пара артикул-количество
class ProductCount
{
public:
    ProductCount(const VendorCode& code, int count);

    const VendorCode& code() const;
    void setCode(const VendorCode& newCode);

    int count() const;
    void setCount(int newCount);

    int& countRef();

private:
    VendorCode _code;
    int _count;
};
