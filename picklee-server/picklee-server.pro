QT += core gui widgets

CONFIG += c++17

SOURCES += \
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
    ui/Description.cpp \
    ui/DescriptionList.cpp \
    ui/EditableLabel.cpp \
    ui/LineEditWidget.cpp

HEADERS += \
    MainWindow.hpp \
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
    ui/Description.hpp \
    ui/DescriptionList.hpp \
    ui/EditableLabel.hpp \
    ui/LineEditWidget.hpp \
    utils/Utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
