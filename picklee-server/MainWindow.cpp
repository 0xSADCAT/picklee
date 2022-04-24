#include "MainWindow.hpp"

#include "ui/ContainerWidget.hpp"
#include "ui/TabPanel.hpp"
#include "ui/customer/CustomerInfoWidget.hpp"
#include "ui/customer/CustomerMainWidget.hpp"
#include "ui/description/DescriptionInfoWidget.hpp"
#include "ui/description/DescriptionMainWidget.hpp"
#include "ui/info/InfoWidget.hpp"
#include "ui/operator/OperatorInfoWidget.hpp"
#include "ui/operator/OperatorMainWidget.hpp"
#include "ui/order/OrderInfoWidget.hpp"
#include "ui/order/OrderMainWidget.hpp"
#include "ui/server/ServerWidget.hpp"
#include "ui/warehouse/WarehouseInfoWidget.hpp"
#include "ui/warehouse/WarehouseMainWidget.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>


MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
  QSplitter* splitter = new QSplitter;
  TabPanel* tabs = new TabPanel;
  ContainerWidget* workArea = new ContainerWidget;
  ContainerWidget* infoArea = new ContainerWidget;

  CustomerInfoWidget* customerInfo = new CustomerInfoWidget;
  CustomerMainWidget* customerMain = new CustomerMainWidget;

  DescriptionInfoWidget* descriptionInfo = new DescriptionInfoWidget;
  DescriptionMainWidget* descriptionMain = new DescriptionMainWidget;

  OperatorInfoWidget* operatorInfo = new OperatorInfoWidget;
  OperatorMainWidget* operatorMain = new OperatorMainWidget;

  OrderInfoWidget* orderInfo = new OrderInfoWidget;
  OrderMainWidget* orderMain = new OrderMainWidget;

  WarehouseInfoWidget* warehouseInfo = new WarehouseInfoWidget;
  WarehouseMainWidget* warehouseMain = new WarehouseMainWidget;

  ServerWidget* serverWidget = new ServerWidget;
  InfoWidget* infoWidget = new InfoWidget;

  workArea->setWidgets(
      {customerMain, descriptionMain, operatorMain, orderMain, warehouseMain, serverWidget, infoWidget});
  infoArea->setWidgets({customerInfo, descriptionInfo, operatorInfo, orderInfo, warehouseInfo});

  QPushButton* customerButton = new QPushButton("Заказчики");
  QPushButton* descriptionButton = new QPushButton("Описания");
  QPushButton* operatorButton = new QPushButton("Операторы");
  QPushButton* orderButton = new QPushButton("Заказы");
  QPushButton* warehouseButton = new QPushButton("Склады");

  QPushButton* serverButton = new QPushButton("Сервер");
  QPushButton* aboutButton = new QPushButton("Информация");

  connect(customerButton, &QPushButton::clicked, this, [workArea, infoArea]() {
    workArea->showWidget(0);
    infoArea->showWidget(0);
  });

  connect(descriptionButton, &QPushButton::clicked, this, [workArea, infoArea]() {
    workArea->showWidget(1);
    infoArea->showWidget(1);
  });

  connect(operatorButton, &QPushButton::clicked, this, [workArea, infoArea]() {
    workArea->showWidget(2);
    infoArea->showWidget(2);
  });

  connect(orderButton, &QPushButton::clicked, this, [workArea, infoArea]() {
    workArea->showWidget(3);
    infoArea->showWidget(3);
  });

  connect(warehouseButton, &QPushButton::clicked, this, [workArea, infoArea]() {
    workArea->showWidget(4);
    infoArea->showWidget(4);
  });

  connect(serverButton, &QPushButton::clicked, this, [workArea]() { workArea->showWidget(5); });

  connect(aboutButton, &QPushButton::clicked, this, [workArea]() { workArea->showWidget(6); });

  tabs->addTopWidget(orderButton);
  tabs->addTopWidget(warehouseButton);
  tabs->addTopWidget(descriptionButton);
  tabs->addTopWidget(customerButton);
  tabs->addTopWidget(operatorButton);

  tabs->addBottomWidget(serverButton);
  tabs->addBottomWidget(aboutButton);

  splitter->addWidget(tabs);
  splitter->addWidget(workArea);
  splitter->addWidget(infoArea);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(splitter);
  setLayout(mainLayout);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  splitter->setStyleSheet("QSplitter::handle{background: #888888;} QSplitter::handle:hover{background: #9de4f1;}");

  /*
   * ***************************************************************************************************************
   * **************************    T E S T    Z O N E      *********************************************************
   * ***************************************************************************************************************
   */

  descriptionMain->addDescription("500.500.23.400", "Ведро гвоздей");
  descriptionMain->addDescription("DOG.22.40.401", "Собака обычная");
  descriptionMain->addDescription("DOG.22.40.401-01", "Собака сутулая");
  descriptionMain->addDescription("137.22.40.200", "Изолетнта");
  descriptionMain->addDescription("000.0000.00000", "Флюгегехаймен");
  descriptionMain->addDescription("SOME-SCARY-THING", "Страшная штуковина");
}


MainWindow::~MainWindow()
{
}
