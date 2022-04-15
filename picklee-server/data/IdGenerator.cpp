#include "IdGenerator.hpp"

#include "Constants.hpp"
#include "DateTime.hpp"
#include "Person.hpp"

#include <QString>


IdGenerator::IdGenerator() : _oper(0), _client(0), _warehouse(0)
{
}


int IdGenerator::generateClient()
{
  return ++_client;
}


int IdGenerator::generateOperator()
{
  return ++_oper;
}


int IdGenerator::generateWarehouse()
{
  return ++_warehouse;
}


std::wstring IdGenerator::generateOrder(const Operator& oper, const Customer& customer)
{
  std::wstring result;

  result += std::to_wstring(oper.id()) + L"-" + std::to_wstring(customer.id()) + L"-";
  result += DateTime::current().toString(L'.');

  return result;
}


void IdGenerator::reset(int oper, int client, int warehouse)
{
  _oper = oper;
  _client = client;
  _warehouse = warehouse;
}


std::tuple<int, int, int> IdGenerator::getAll() const
{
  return {_oper, _client, _warehouse};
}
