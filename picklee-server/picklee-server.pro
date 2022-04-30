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
    ui/EditableWidget.cpp \
    ui/ProductDescriptionWidget.cpp

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
    ui/EditableWidget.hpp \
    ui/ProductDescriptionWidget.hpp \
    utils/Utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
