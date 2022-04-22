#include "MainWindow.hpp"
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

  CHECK(oper, Operator);
  CHECK(cust, Customer);
  CHECK(desc, ProductDescription);
  CHECK(prod, ProductCount);
  CHECK(order, Order);
  CHECK(ware, Warehouse);

  return 0;

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
