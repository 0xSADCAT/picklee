#pragma once

#include <string>


class Convertor;


/// Артикул
class VendorCode
{
public:
    static inline const std::wstring className = L"VendorCode";

    VendorCode(const std::wstring& code);

    std::wstring str() const;

private:
    std::wstring _str;
};


bool operator==(const VendorCode& left, const VendorCode& right);
bool operator!=(const VendorCode& left, const VendorCode& right);


/// Пара артикул-описание
class ProductDescription
{
public:
    static inline const std::wstring className = L"ProductDescription";

    ProductDescription(const VendorCode& code, const std::wstring& description);

    const VendorCode& code() const;
    void setCode(const VendorCode& newCode);

    const std::wstring& description() const;
    void setDescription(const std::wstring& newDescription);

    void convert(Convertor& convertor) const;

private:
    VendorCode _code;
    std::wstring _description;
};


/// Пара артикул-количество
class ProductCount
{
public:
    static inline const std::wstring className = L"ProductCount";

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
