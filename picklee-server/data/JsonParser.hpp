#pragma once

#include "I_Parser.hpp"


class JsonParser : public I_Parser
{
public:
  JsonParser() noexcept = default;

  virtual void parse(const std::wstring& string) noexcept override;

  virtual std::vector<Order> orders() const noexcept override;
  virtual std::vector<Operator> operators() const noexcept override;
  virtual std::vector<Customer> customers() const noexcept override;
  virtual std::vector<ProductDescription> descriptions() const noexcept override;
  virtual std::vector<Warehouse> warehouses() const noexcept override;

  virtual void loadTo(std::back_insert_iterator<std::vector<Order>> inserter) const noexcept override;
  virtual void loadTo(std::back_insert_iterator<std::vector<Operator>> inserter) const noexcept override;
  virtual void loadTo(std::back_insert_iterator<std::vector<Customer>> inserter) const noexcept override;
  virtual void loadTo(std::back_insert_iterator<std::vector<ProductDescription>> inserter) const noexcept override;
  virtual void loadTo(std::back_insert_iterator<std::vector<Warehouse>> inserter) const noexcept override;

  virtual std::vector<std::pair<std::wstring_view, std::wstring>> errors() const noexcept override;

  virtual void clear() noexcept override;

private:
  std::vector<Order> _orders;
  std::vector<Operator> _operators;
  std::vector<Customer> _customers;
  std::vector<ProductDescription> _descriptions;
  std::vector<Warehouse> _warehouses;

  std::vector<std::pair<std::wstring_view, std::wstring>> _errorList;

  void pushError(std::wstring_view err, const std::wstring& string) noexcept;
  static bool isBrackestValid(const std::wstring& string);

  Order parseOrder(const std::wstring& string);
  Operator parseOperator(const std::wstring& string);
  Customer parseCustomer(const std::wstring& string);
  Person parsePerson(const std::wstring& string);
  ProductDescription parseDescription(const std::wstring& string);
  std::vector<ProductCount> parseCount(const std::wstring& string) noexcept;
  Warehouse parseWarehouse(const std::wstring& string);
};

