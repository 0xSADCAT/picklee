QT += core gui widgets

CONFIG += c++17

SOURCES += \
    Settings.cpp \
    data/DBIO.cpp \
    data/DataBase.cpp \
    data/DateTime.cpp \
    data/Filter.cpp \
    data/IdGenerator.cpp \
    data/Order.cpp \
    data/Person.cpp \
    data/Product.cpp \
    data/Warehouse.cpp \
    main.cpp \
    MainWindow.cpp \
    ui/ContainerWidget.cpp \
    ui/EditableLabel.cpp \
    ui/LineEditWidget.cpp \
    ui/TabPanel.cpp \
    ui/customer/CustomerInfoWidget.cpp \
    ui/customer/CustomerMainWidget.cpp \
    ui/customer/CustomerWidget.cpp \
    ui/description/DescriptionInfoWidget.cpp \
    ui/description/DescriptionMainWidget.cpp \
    ui/description/DescriptionWidget.cpp \
    ui/info/InfoWidget.cpp \
    ui/operator/OperatorInfoWidget.cpp \
    ui/operator/OperatorMainWidget.cpp \
    ui/order/OrderInfoWidget.cpp \
    ui/order/OrderMainWidget.cpp \
    ui/server/ServerWidget.cpp \
    ui/warehouse/WarehouseInfoWidget.cpp \
    ui/warehouse/WarehouseMainWidget.cpp

HEADERS += \
    MainWindow.hpp \
    Settings.hpp \
    data/DBIO.hpp \
    data/DataBase.hpp \
    data/DateTime.hpp \
    data/Exceptions.hpp \
    data/Filter.hpp \
    data/I_DataBase.hpp \
    data/I_FileIO.hpp \
    data/IdGenerator.hpp \
    data/Order.hpp \
    data/Person.hpp \
    data/Product.hpp \
    data/Warehouse.hpp \
    ui/ContainerWidget.hpp \
    ui/EditableLabel.hpp \
    ui/LineEditWidget.hpp \
    ui/TabPanel.hpp \
    ui/customer/CustomerInfoWidget.hpp \
    ui/customer/CustomerMainWidget.hpp \
    ui/customer/CustomerWidget.hpp \
    ui/description/DescriptionInfoWidget.hpp \
    ui/description/DescriptionMainWidget.hpp \
    ui/description/DescriptionWidget.hpp \
    ui/info/InfoWidget.hpp \
    ui/operator/OperatorInfoWidget.hpp \
    ui/operator/OperatorMainWidget.hpp \
    ui/order/OrderInfoWidget.hpp \
    ui/order/OrderMainWidget.hpp \
    ui/server/ServerWidget.hpp \
    ui/warehouse/WarehouseInfoWidget.hpp \
    ui/warehouse/WarehouseMainWidget.hpp \
    utils/Utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
