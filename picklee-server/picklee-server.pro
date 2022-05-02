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
    ui/CustomerWidget.cpp \
    ui/EditableList.cpp \
    ui/EditableWidget.cpp \
    ui/OperatorWidget.cpp \
    ui/OrderWidget.cpp \
    ui/ProductCountWidget.cpp \
    ui/ProductDescriptionWidget.cpp \
    ui/SpoilerWidget.cpp \
    ui/WarehouseWidget.cpp

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
    ui/CustomerWidget.hpp \
    ui/EditableList.hpp \
    ui/EditableWidget.hpp \
    ui/OperatorWidget.hpp \
    ui/OrderWidget.hpp \
    ui/ProductCountWidget.hpp \
    ui/ProductDescriptionWidget.hpp \
    ui/SpoilerWidget.hpp \
    ui/WarehouseWidget.hpp \
    utils/Utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
