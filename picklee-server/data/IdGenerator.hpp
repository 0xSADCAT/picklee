#pragma once

#include <QString>
#include <tuple>


class Operator;
class Customer;


/// Генератор идендификаторов
class IdGenerator
{
public:
    IdGenerator();
    IdGenerator(int oper, int client, int warehouse);

    int generateClient();
    int generateOperator();
    int generateWarehouse();

    static QString generateOrder(const Operator& oper, const Customer& customer);

    /**
     * @brief Получить текущие значения счетчиков
     * @return Счетчики для: <оператор, клиент, склад>
     */
    std::tuple<int, int, int> getAll() const;

private:
    int _oper;
    int _client;
    int _warehouse;
};
