QT += quick
QT += serialbus
QT += widgets
QT += gui
QT += core
QT += quickcontrols2


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        GPIO_pin.cpp \
        SendData.cpp \
        comboboxmodel.cpp \
        counter.cpp \
        formatinput.cpp \
        gpio_handler.cpp \
        main.cpp \
        recieveframes.cpp

RESOURCES += qml.qrc
RESOURCES += delete.png

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    FormatInput.h \
    GPIO_pin.h \
    SendData.h \
    comboboxmodel.h \
    counter.h \
    gpio_handler.h \
    recieveFrames.h
