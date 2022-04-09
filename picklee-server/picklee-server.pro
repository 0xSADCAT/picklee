QT += core gui widgets

CONFIG += c++17

SOURCES += \
    data/Convertor.cpp \
    data/DataBase.cpp \
    data/Filter.cpp \
    data/IdGenerator.cpp \
    data/Order.cpp \
    data/Person.cpp \
    data/Product.cpp \
    data/Warehouse.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.hpp \
    data/Constants.hpp \
    data/Convertor.hpp \
    data/DataBase.hpp \
    data/Filter.hpp \
    data/I_DataBase.hpp \
    data/IdGenerator.hpp \
    data/Order.hpp \
    data/Person.hpp \
    data/Product.hpp \
    data/Warehouse.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
