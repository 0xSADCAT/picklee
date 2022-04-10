#include "MainWindow.hpp"
#include "data/Convertor.hpp"
#include "data/DataBase.hpp"

#include <QApplication>
#include <iostream>
#include <string>


using namespace std::string_literals;

/*
 * база данных:
 *     - последний id:
 *         - клиент
 *         - оператор
 *         - склад
 *     - описания продуктов:
 *         - артикул
 *         - описание
 *     - клиенты:
 *         - id
 *         - имя
 *         - дата рождения
 *     - операторы:
 *         - id
 *         - имя
 *     - заказы:
 *         - id
 *         - статус
 *         - состав:
 *             - артикул
 *             - количество
 *     - склады:
 *         - id
 *         - описание
 *         - приоритет
 *         - продукты:
 *             - артикул
 *             - количество
 */


int main(int argc, char *argv[])
{
    JsonConvertor conv;
    IdGenerator idGenerator;
    idGenerator.reset(24, 377, 2);

    Operator oper(idGenerator.generateOperator(), Person(L"John"s, L"Johnson"s, L"Johnsovich"s));
    Customer cust(idGenerator.generateClient(), Person(L"Albert"s, L"Testoviy"s, L"Mahmudovich"s));
    ProductDescription desc({L"12345-222"s}, L"Some shit"s);
    ProductCount prod(desc.code(), 14);
    Order order(idGenerator.generateOrder(oper, cust), oper.id(), cust.id(), {prod, ProductCount({L"3213555"s}, 200)}, Order::Status::WaitingForDelivery);
    Warehouse ware(200, -4, L"BigTIHS"s);
    ware.deliver({desc.code(), 400});
    ware.deliver({{L"00000"s}, 1});

    oper.convert(conv);
    cust.convert(conv);
    desc.convert(conv);
    prod.convert(conv);
    order.convert(conv);
    ware.convert(conv);

    std::wcout << conv.result() << std::endl;

    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
