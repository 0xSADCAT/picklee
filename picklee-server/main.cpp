#include "MainWindow.hpp"
#include "data/Convertor.hpp"
#include "data/DataBase.hpp"
#include "data/JsonLoader.hpp"

#include <QApplication>
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
  JsonConvertor conv;
  IdGenerator idGenerator;
  idGenerator.reset(24, 377, 2);

  Operator oper(idGenerator.generateOperator(), Person(L"John", L"Johnson", L"Johnsovich"));
  Customer cust(idGenerator.generateClient(), Person(L"Albert", L"Testoviy", L"Mahmudovich"));
  ProductDescription desc({L"12345-222"}, L"Some shit");
  ProductCount prod(desc.code(), 14);
  Order order(idGenerator.generateOrder(oper, cust),
              oper.id(),
              cust.id(),
              {prod, ProductCount({L"3213555"}, 200)},
              Order::Status::WaitingForDelivery);
  Warehouse ware(200, -4, L"BigTIHS");
  ware.deliver({desc.code(), 400});
  ware.deliver({{L"00000"}, 1});

  DataBase db;
  JsonLoader loader(db);

  oper.convert(conv);
  loader.loadFrom(conv.result());
  conv.clear();

  cust.convert(conv);
  loader.loadFrom(conv.result());
  conv.clear();

  order.convert(conv);
  loader.loadFrom(conv.result());
  conv.clear();

  ware.convert(conv);
  loader.loadFrom(conv.result());
  conv.clear();

  return 0;

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
