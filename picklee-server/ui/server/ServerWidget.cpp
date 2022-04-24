#include "ServerWidget.hpp"

#include <QLabel>
#include <QVBoxLayout>


ServerWidget::ServerWidget(QWidget *parent)
    : QWidget{parent}
{
  auto l = new QVBoxLayout;
  l->addWidget(new QLabel("Server info\nIn DEV"));
  setLayout(l);
}
