#pragma once

#include <QString>


class Convertor;


/// Артикул
class VendorCode
{
public:
    static inline const QString className = "VendorCode";

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
    static inline const QString className = "ProductDescription";

    ProductDescription(const VendorCode& code, const QString& description);

    const VendorCode& code() const;
    void setCode(const VendorCode& newCode);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    void convert(Convertor& convertor) const;

private:
    VendorCode _code;
    QString _description;
};


/// Пара артикул-количество
class ProductCount
{
public:
    static inline const QString className = "ProductCount";

    ProductCount(const VendorCode& code, int count);

    const VendorCode& code() const;
    void setCode(const VendorCode& newCode);

    int count() const;
    void setCount(int newCount);

    int& countRef();

    void convert(Convertor& convertor) const;

private:
    VendorCode _code;
    int _count;
};
