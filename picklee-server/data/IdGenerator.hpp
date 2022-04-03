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

    int generateClient();
    int generateOperator();
    int generateWarehouse();

    static QString generateOrder(const Operator& oper, const Customer& customer);

    /**
     * @brief Установить новые значения счетчиков идентификаторов
     * @param oper Для операторов
     * @param client Для клиентов
     * @param warehouse Для складов
     */
    void reset(int oper, int client, int warehouse);

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
