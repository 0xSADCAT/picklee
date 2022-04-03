#pragma once

#include "IdGenerator.hpp"
#include "Order.hpp"
#include "Person.hpp"
#include "Product.hpp"
#include "Warehouse.hpp"

#include <QList>
#include <QString>


class DataBase
{
public:
    DataBase() = default;


private:
    IdGenerator _idGenerator;
    QList<Order> _orders;
    QList<Operator> _operators;
    QList<Customer> _customers;
    QList<Warehouse> _warehouses;
    QList<ProductDescription> _descriptions;
};
