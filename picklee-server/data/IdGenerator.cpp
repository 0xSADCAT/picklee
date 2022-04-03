#include "Constants.hpp"
#include "IdGenerator.hpp"
#include "Person.hpp"

#include <QDateTime>


IdGenerator::IdGenerator()
    : _oper(0),
      _client(0),
      _warehouse(0)
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


QString IdGenerator::generateOrder(const Operator& oper, const Customer& customer)
{
    QString result;

    result += QString::number(oper.id()) + "-" + QString::number(customer.id()) + "-";
    result += QDateTime::currentDateTime().toString(*dateTimeFormat);

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
