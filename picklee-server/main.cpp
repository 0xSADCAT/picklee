#include "MainWindow.hpp"
#include "data/DBIO.hpp"
#include "data/DataBase.hpp"

#include <QApplication>
#include <iostream>
#include <string>


void ok(std::wstring_view name)
{
  std::wcout << name << L" <- OK" << std::endl;
}


void err(std::wstring_view name)
{
  std::wcout << name << L" <- ERR" << std::endl;
}


void check(bool cond, std::wstring_view name)
{
  if (cond)
  {
    ok(name);
  }
  else
  {
    err(name);
  }
}


#define CHECK(val, name)                                                                   \
  try                                                                                      \
  {                                                                                        \
    check(val.toString() == name::fromString(val.toString()).toString(), name::className); \
  }                                                                                        \
  catch (...)                                                                              \
  {                                                                                        \
    err(name::className);                                                                  \
  }


int main(int argc, char* argv[])
{
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

  Operator oper2(idGenerator.generateOperator(), Person(L"John2", L"Johnson2", L"Johnsovich2"));
  Customer cust2(idGenerator.generateClient(), Person(L"Albert2", L"Testoviy2", L"Mahmudovich2"));
  ProductDescription desc2({L"500-222"}, L"Some shit2");
  ProductCount prod2(desc.code(), 14);
  Order order2(idGenerator.generateOrder(oper, cust),
               oper.id(),
               cust.id(),
               {prod2, ProductCount({L"255-35-35"}, 200)},
               Order::Status::WaitingForDelivery);
  Warehouse ware2(200, -4, L"BigTIHS");
  ware.deliver({desc2.code(), 2000});
  ware.deliver({{L"11111"}, 6});

  CHECK(oper, Operator);
  CHECK(cust, Customer);
  CHECK(desc, ProductDescription);
  CHECK(prod, ProductCount);
  CHECK(order, Order);
  CHECK(ware, Warehouse);

  DBIO io("picklee-test/");

  io.saveCustomers({cust, cust2});
  io.saveDescriptions({desc, desc2});
  io.saveOperators({oper, oper2});
  io.saveOrders({order, order2});
  io.saveWarehouses({ware, ware2});

  return 0;

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
