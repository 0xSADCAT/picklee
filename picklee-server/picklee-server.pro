QT += core gui widgets

CONFIG += c++17

SOURCES += \
    data/Convertor.cpp \
    data/DataBase.cpp \
    data/DateTime.cpp \
    data/Filter.cpp \
    data/IdGenerator.cpp \
    data/JsonLoader.cpp \
    data/JsonParser.cpp \
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
    data/DateTime.hpp \
    data/Filter.hpp \
    data/I_DataBase.hpp \
    data/I_Loader.hpp \
    data/I_Parser.hpp \
    data/IdGenerator.hpp \
    data/JsonLoader.hpp \
    data/JsonParser.hpp \
    data/Order.hpp \
    data/Person.hpp \
    data/Product.hpp \
    data/Warehouse.hpp \
    utils/Utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
