#include "Constants.hpp"
#include "IdGenerator.hpp"
#include "Person.hpp"

#include <QDateTime>


IdGenerator::IdGenerator()
    : IdGenerator(0, 0, 0)
{
}


IdGenerator::IdGenerator(int oper, int client, int warehouse)
    : _oper(oper),
      _client(client),
      _warehouse(warehouse)
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


std::tuple<int, int, int> IdGenerator::getAll() const
{
    return {_oper, _client, _warehouse};
}
